DOC=EOF

all: $(DOC).pdf

$(DOC).pdf: $(DOC).dvi $(DOC).idx
	dvipdf $<

$(DOC).idx $(DOC).dvi: $(DOC).tex
	latex $<
	latex $<
	latex $<

$(DOC).ind: $(DOC).idx
	makeindex $(DOC)

viewdoc: all
	evince EOF.pdf
