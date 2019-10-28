#lang racket

(provide crazy2val)

(define (crazy2val c)
	(if (null? c) 0 (let ((x (car c)) (y (* 2 (crazy2val (cdr c))))) 
(if (equal? 'p x) (+ y 1) (if (equal? 'n x) (- y 1) y)))))
