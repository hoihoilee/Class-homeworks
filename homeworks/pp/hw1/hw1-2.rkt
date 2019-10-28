#lang racket

(provide crazy2add)

(define (crazy2add lhs rhs)
	(if (null? lhs) rhs (if (null? rhs) lhs
	(let ((l (car lhs)) (r (car rhs)) (lh (cdr lhs)) (rh (cdr rhs)))
	(if (equal? l r) (cons 'z (crazy2add (crazy2add (cons l '()) lh) rh))
	(if (equal? l 'z) (cons r (crazy2add lh rh))
	(if (equal? r 'z) (cons l (crazy2add lh rh))
	(cons 'z (crazy2add lh rh)))))))))
