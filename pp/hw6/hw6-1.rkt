#lang racket

;;; If these statements are omitted, your submission will be graded 0.
(provide memo-ways)

(define history '())

(define (memo-ways n m) ; memo-ways: int * int -> int
	(define (member? n m l)
	(if (null? l) -1
	(let ((x (car l)))
	(if (equal? (cons n m) (car x)) (cadr x) (member? n m (cdr l))))))
	
	(if (or (equal? n 0) (equal? m 0)) 1
	(let ((mem (member? n m history)))
	(if (equal? mem -1)
	(let ((x (+ (memo-ways (- n 1) m) (memo-ways n (- m 1)))))
	(set! history (cons (list (cons n m) x) history)) x) mem))))
