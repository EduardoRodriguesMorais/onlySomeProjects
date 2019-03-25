ARG BASE_TAG=5.2.0

FROM gcr.io/kaggle-images/python-tensorflow-whl:1.13.1-py36 as tensorflow_whl
FROM continuumio/anaconda3:${BASE_TAG}

ADD clean-layer.sh  /tmp/clean-layer.sh
ADD patches/nbconvert-extensions.tpl /opt/kaggle/nbconvert-extensions.tpl

# This is necessary for apt to access HTTPS sources
RUN apt-get update && \
    apt-get install apt-transport-https && \
    /tmp/clean-layer.sh

# Tensorflow doesn't support python 3.7 yet. See https://github.com/tensorflow/tensorflow/issues/20517	
# Fix to install Tensorflow: Downgrade python 3.7->3.6.6.
RUN conda install -y python=3.6.6 && \
    /tmp/clean-layer.sh

# The anaconda base image includes outdated versions of these packages. Update them to include the latest version.
RUN pip install --upgrade seaborn python-dateutil dask && \
    pip install pyyaml joblib pytagcloud husl geopy ml_metrics mne pyshp && \
    conda install -y -c conda-forge spacy && python -m spacy download en && \
    python -m spacy download en_core_web_lg && \
    pwd && ls -al && ./configure && \
    make -j $(nproc) && make install && \
    /tmp/clean-layer.sh

# Install tensorflow from a pre-built wheel
COPY --from=tensorflow_whl /tmp/tensorflow_cpu/*.whl /tmp/tensorflow_cpu/
RUN pip install /tmp/tensorflow_cpu/tensorflow*.whl && \
    rm -rf /tmp/tensorflow_cpu && \
    /tmp/clean-layer.sh

    #Ferramenta de análise de rede 
RUN conda install -y -c conda-forge python-igraph && \
    
    #Redes neurais em Theano(Otimizador de compilador)
    pip install git+git://github.com/Lasagne/Lasagne.git && \  
    
    # Dev branch of Theano
    pip install git+git://github.com/Theano/Theano.git --upgrade --no-deps && \
    
    # put theano compiledir inside /tmp (it needs to be in writable dir)
    printf "[global]\nbase_compiledir = /tmp/.theano\n" > /.theanorc && \
    cd /usr/local/src &&  git clone --depth 1 https://github.com/pybrain/pybrain && \
    cd pybrain && python setup.py install && \
    
    #Reforço de aprendizado profundo(keras-rl)
    pip install keras && \
    pip install keras-rl && \   

    #neon - Estrutura de aprendizagem profunda da Intel (Melhor desempenho hardware)
    cd /usr/local/src && \
    git clone --depth 1 https://github.com/NervanaSystems/neon.git && \
    cd neon && pip install . && \
    
    /tmp/clean-layer.sh

# Make sure the dynamic linker finds the right libstdc++
ENV LD_LIBRARY_PATH=/opt/conda/lib

    #API orientada a objetos para incorporar gráficos
RUN pip install matplotlib && \
    
    pip install --upgrade numpy && \
    
    # h2o - Plataforma de análise preditiva e de aprendizado de máquina (requires java)
    # requires java
    apt-get install -y default-jdk && \
    cd /usr/local/src && mkdir h2o && cd h2o && \
    wget --no-verbose http://h2o-release.s3.amazonaws.com/h2o/latest_stable -O latest && \
    wget --no-verbose --no-check-certificate -i latest -O h2o.zip && rm latest && \
    unzip h2o.zip && rm h2o.zip && cp h2o-*/h2o.jar . && \
    pip install `find . -name "*whl"` && \
    
    # Keras setup
    # Keras likes to add a config file in a custom directory when it's
    # first imported. This doesn't work with our read-only filesystem, so we
    # have it done now
    python -c "from keras.models import Sequential"  && \
    # Switch to TF backend
    sed -i 's/theano/tensorflow/' /root/.keras/keras.json  && \
    # Re-run it to flush any more disk writes
    python -c "from keras.models import Sequential; from keras import backend; print(backend._BACKEND)" && \
    # Keras reverts to /tmp from ~ when it detects a read-only file system
    mkdir -p /tmp/.keras && cp /root/.keras/keras.json /tmp/.keras && \
    /tmp/clean-layer.sh

    #scikit-learn dependencies (Biblioteca de aprendizado de máquina) 
RUN pip install scipy && \
    pip install scikit-learn && \
    # HDF5 support ()
    conda install h5py && \
    # PUDB, for local debugging convenience
    pip install pudb && \
    # Imbalanced-learn
    cd /usr/local/src && git clone https://github.com/scikit-learn-contrib/imbalanced-learn.git && \
    cd imbalanced-learn && python setup.py install && \ 
    #Vizualização de gráficos 
    conda install -y -c bokeh bokeh && \
    #Sistema de pipe line de gráficos
    pip install datashader && \
    /tmp/clean-layer.sh

    #Aumentar imagens 
RUN pip install imgaug && \
    #Biblioteca de gráficos
    pip install plotly && \
    # tflean. Deep learning library featuring a higher-level API for TensorFlow. http://tflearn.org
    pip install git+https://github.com/tflearn/tflearn.git && \
    # fitter 1.1.10 is broken. Fails at setup with:
    # install_requires = open("requirements.txt").read(),
    # FileNotFoundError: [Errno 2] No such file or directory: 'requirements.txt'
    pip install fitter==1.0.9 && \
    pip install langid && \
    # Delorean. Useful for dealing with datetime
    pip install delorean && \
    /tmp/clean-layer.sh

    #Add google PAIR-code Facets (visão de alto nível de conjuntos de dados)
RUN cd /opt/ && git clone https://github.com/PAIR-code/facets && cd facets/ && jupyter nbextension install facets-dist/ --user && \
    export PYTHONPATH=$PYTHONPATH:/opt/facets/facets_overview/python/ && \
    #Verifica consumo de memória pro python
    pip install memory_profiler && \
    /tmp/clean-layer.sh

    # yellowbrick machine learning (Visualização de aprendizado de máquina)
RUN pip install yellowbrick && \
    pip install mlcrate && \
    # Required to display Altair charts in Jupyter notebook
    pip install vega3 && \
    jupyter nbextension install --sys-prefix --py vega3 && \
    /tmp/clean-layer.sh

# Fast.ai and dependencies
RUN pip install bcolz && \
    pip install bleach && \
    pip install certifi && \
    pip install cycler && \
    pip install decorator && \
    pip install entrypoints && \
    pip install html5lib && \
    pip install ipykernel && \
    pip install ipython && \
    pip install ipython-genutils && \
    pip install ipywidgets && \
    pip install isoweek && \
    pip install jedi && \
    pip install Jinja2 && \
    pip install jsonschema && \
    pip install jupyter && \
    pip install jupyter-client && \
    pip install jupyter-console && \
    pip install jupyter-core && \
    pip install MarkupSafe && \
    pip install mistune && \
    pip install nbconvert && \
    pip install nbformat && \
    pip install notebook==5.5.0 && \
    pip install olefile && \
    pip install opencv-python && \
    # b/124184516: tsfresh is not yet compatible with pandas 0.24.0
    pip install pandas==0.23.4 && \
    pip install pandas_summary && \
    pip install pandocfilters && \
    pip install pexpect && \
    pip install pickleshare && \
    pip install Pillow && \
    pip install ptyprocess && \
    pip install Pygments && \
    pip install pyparsing && \
    pip install python-dateutil==2.6.0 && \
    pip install pytz && \
    pip install PyYAML && \
    pip install pyzmq && \
    pip install qtconsole && \
    pip install simplegeneric && \
    pip install six && \
    pip install terminado && \
    pip install testpath && \
    pip install tornado && \
    pip install tqdm && \
    pip install traitlets && \
    pip install wcwidth && \
    pip install webencodings && \
    pip install widgetsnbextension && \
    # Latest version of pyarrow conflicts with pandas
    pip install pyarrow==0.10.0 && \
    pip install feather-format && \
    pip install fastai && \
    pip install torchtext && \
    /tmp/clean-layer.sh

    #Integração Keras com barras de progresso
RUN pip install keras-tqdm && \
    #Aprendizado de reforço aplicado
    pip install tensorforce && \
    #Transferência de aprendizagem
    pip install tensorflow_hub && \
    #Métodos de regressão ou classificação
    pip install tsfresh && \
    #Estrutura de otimização de hiperparâmetros
    pip install optuna && \
    /tmp/clean-layer.sh

# For Facets
ENV PYTHONPATH=$PYTHONPATH:/opt/facets/facets_overview/python/
# For Theano with MKL
ENV MKL_THREADING_LAYER=GNU

    #Temporary fixes and patches
    #Temporary patch for Dask getting downgraded, which breaks Keras
RUN pip install --upgrade dask && \
    # Stop jupyter nbconvert trying to rewrite its folder hierarchy
    mkdir -p /root/.jupyter && touch /root/.jupyter/jupyter_nbconvert_config.py && touch /root/.jupyter/migrated && \
    mkdir -p /.jupyter && touch /.jupyter/jupyter_nbconvert_config.py && touch /.jupyter/migrated && \
    # Stop Matplotlib printing junk to the console on first load
    sed -i "s/^.*Matplotlib is building the font cache using fc-list.*$/# Warning removed by Kaggle/g" /opt/conda/lib/python3.6/site-packages/matplotlib/font_manager.py && \
    # Make matplotlib output in Jupyter notebooks display correctly
    mkdir -p /etc/ipython/ && echo "c = get_config(); c.IPKernelApp.matplotlib = 'inline'" > /etc/ipython/ipython_config.py && \
    /tmp/clean-layer.sh

# Add BigQuery client proxy settings
ENV PYTHONUSERBASE "/root/.local"
ADD patches/kaggle_gcp.py /root/.local/lib/python3.6/site-packages/kaggle_gcp.py
ADD patches/kaggle_secrets.py /root/.local/lib/python3.6/site-packages/kaggle_secrets.py
ADD patches/sitecustomize.py /root/.local/lib/python3.6/site-packages/sitecustomize.py

# TensorBoard Jupyter extension. Should be replaced with TensorBoard's provided magic once we have
# worker tunneling support in place.
ENV JUPYTER_CONFIG_DIR "/root/.jupyter/"
RUN pip install jupyter_tensorboard && \
    jupyter serverextension enable jupyter_tensorboard && \
    jupyter tensorboard enable
ADD patches/tensorboard/notebook.py /opt/conda/lib/python3.6/site-packages/tensorboard/notebook.py

# Set backend for matplotlib
ENV MPLBACKEND "agg"