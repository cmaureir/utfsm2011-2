TEX = $(wildcard *.tex)
PDF = $(TEX:.tex=.pdf)

pdf:  $(PDF)

%.pdf: %.tex
	@rubber --pdf $<
clean:
	@rubber --clean --pdf $(TEX:.tex=)
	@rm -f *.{vrb,out,spl}
x:
	@okular $(PDF) &> /dev/null &
.PHONY: pdf clean

