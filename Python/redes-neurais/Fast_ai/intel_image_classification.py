import numpy as np 
import pandas as pd 
from pathlib import Path

from fastai import *
from fastai.vision import *
from fastai.callbacks import *
import os

def print_results(cm):
    tp = cm[0][0] 
    tn = cm[1][1]
    fn = cm[0][1]
    fp = cm[1][0]
    accuracy = (tp + tn) / (tp + tn + fp + fn)
    sensitivity = tp / (tp + fn)
    specificity = tn / (tn + fp)
    print("Accuracy: %f\n Sensitivity : %f\n Specificity: %f" %(accuracy,sensitivity,specificity))

data_folder = Path("../input")
data_folder.ls()



transforms = get_transforms(do_flip = True, 
                            flip_vert = True, 
                            max_rotate = 100.0, 
                            max_zoom = 1.5, 
                            max_lighting = 0.2, 
                            max_warp = 0.2, 
                            p_affine = 0.75, 
                            p_lighting = 0.75)

data = (ImageList.from_folder(path=data_folder)
        .split_by_folder('seg_train', 'seg_test')
        .label_from_folder()
        .add_test_folder('seg_pred')
        .transform(transforms, size=224)
        .databunch(path='.', bs=32)
        .normalize(imagenet_stats)
       )

data




data.classes
data.show_batch(rows = 6)

learn = cnn_learner(data, models.resnet50, metrics = [accuracy], model_dir = '/tmp/model/')


reduce_lr = ReduceLROnPlateauCallback( learn, patience = 5, factor = 0.2, monitor = 'accuracy')
early_stopping = EarlyStoppingCallback( learn, patience = 10, monitor = 'accuracy')
save_model = SaveModelCallback( learn, monitor = 'accuracy', every = 'improvement')
callbaks = [reduce_lr, early_stopping, save_model]

learn.unfreeze()
learn.lr_find()
learn.recorder.plot(suggestion = True)


min_grad_lr = learn.recorder.min_grad_lr
learn.fit_one_cycle(50, min_grad_lr, callbaks)
learn.save('model')


learn.recorder.plot_losses()

learn.recorder.plot_metrics()

interp = ClassificationInterpretation.from_learner(learn)
mtz = interp.confusion_matrix(slice_size=10)
print_results(mtz)

interp.plot_confusion_matrix()

interp.plot_top_losses(9, figsize = (12, 12))

