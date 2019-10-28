#lang racket

(require "hw1-2.rkt")
(provide crazy2mul)
(provide make_negative)

(define (crazy2mul lhs rhs)
        (if (null? rhs) '()
	(let ((r (car rhs)) (y (cons 'z (crazy2mul lhs (cdr rhs)))))
	(if (equal? r 'p) (crazy2add lhs y)
	(if (equal? r 'n) (crazy2add (make_negative lhs) y) y)))))

(define (make_negative c)
	(if (null? c) '()
	(let ((x (car c)) (y (cdr c)))
	(if (equal? x 'p) (cons 'n (make_negative y))
	(if (equal? x 'n) (cons 'p (make_negative y))
	(cons 'z (make_negative y)))))))
