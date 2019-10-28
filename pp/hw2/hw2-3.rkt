#lang racket

(provide iter)

(define (iter n f)
	(if (equal? n 0) (lambda (x) x)
	(lambda (x) (f ((iter (- (abs n) 1) f) x)))))	 
