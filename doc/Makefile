# XTL - the eXternalization Template Library (documentation)
# Copyright (C) 1998, 1999 Jose' Orlando Pereira, Universidade do Minho
# 
# jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
# 
# Departamento de Informatica, Universidade do Minho
# Campus de Gualtar, 4710-057 Braga, Portugal
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
# MA 02111-1307, USA
#
# $Id: Makefile,v 1.1 2005/02/24 05:24:06 philgrim Exp $

all: xtlguide.ps xtlguide.pdf

xtlguide.ps: xtlguide.dvi
	dvips -o xtlguide.ps xtlguide.dvi

xtlguide.aux: xtlguide.tex arch.ps
	latex xtlguide.tex
	
xtlguide.bbl: xtlguide.aux xtl.bib
	bibtex xtlguide || true

xtlguide.dvi: xtlguide.bbl xtlguide.tex
	latex xtlguide.tex
	latex xtlguide.tex

arch.ps: arch.fig
	fig2dev -L ps arch.fig arch.ps

xtlguide.pdf: xtlguide.ps
	ps2pdf xtlguide.ps

clean:
	rm -f *.dvi *.log *.aux *.blg *.bbl *.ps *.pdf *.eps *~

