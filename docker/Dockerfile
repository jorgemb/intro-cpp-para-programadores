FROM quay.io/jupyter/base-notebook:conda-25.3.1

RUN conda install --solver=classic conda-forge::xeus-cling -y
ENTRYPOINT [ "start.sh", "jupyter", "lab", "--NotebookApp.token", "''"]