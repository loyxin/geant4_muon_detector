all: ppt.pdf
ppt.pdf:clean ppt.tex
	xelatex ppt.tex
	xelatex ppt.tex
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl *.nav *.snm
clean:
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl *.nav *.snm ppt.pdf
