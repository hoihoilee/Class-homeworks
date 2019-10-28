#lang racket

(provide inl inr case-sum)

(define (inl v) (cons v 'l))

(define (inr v) (cons v 'r))

(define (case-sum f1 f2 s)
	(if (equal? (cdr s) 'l) (f1 (car s))
	(f2 (car s))))
