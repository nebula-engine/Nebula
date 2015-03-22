dot_files = $(shell find dot/ -name "*.dot")
png_files = $(patsubst %.dot, build/%.png, $(dot_files))

all:
	doxygen Doxyfile

graphs: $(png_files)
	@#echo png_files

$(png_files): build/%.png: %.dot
	@mkdir -p $(dir $@)
	dot $< -Tpng -o$@

