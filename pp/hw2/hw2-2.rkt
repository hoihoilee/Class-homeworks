#lang racket

(provide zipperN)

(define (zipperN l)
	(if (null? l) l
	(if (null? (car l)) (zipperN (cdr l))
	(cons (car (car l)) (zipperN (append (cdr l) (list (cdr (car l)))))))))
