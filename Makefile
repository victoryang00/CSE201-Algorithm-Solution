SHELL := /bin/bash
ALL:
	number=5 ; while [[ $$number -le 5 ]] ; do \
		echo "Number: $$number" ; \
		num1=`echo $${number}|awk '{printf("%02d\n",$$0)}'`; \
		echo "num1: $$num1" ; \
		xelatex -interaction=nonstopmode -shell-escape hw$${num1}.tex || true; \
		((number = number + 1)) ; \
	done
	