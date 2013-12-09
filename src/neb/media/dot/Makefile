dot_files    := $(shell find . -name '*.dot')

pdf_files    := $(patsubst %.dot, %.pdf, $(dot_files))

all: $(pdf_files)

%.pdf: %.dot
	@dot -Tpdf -o $@ $<


