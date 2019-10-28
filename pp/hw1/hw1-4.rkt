#lang racket
(provide number_of)
(provide leaf node)
(provide is-empty-tree? is-leaf? leaf-val nth-child)

(define (number_of l)
	(if (null? l) 0
	(+ 1 (number_of (cdr l)))))

(define (leaf n) (list 'Leaf n))
	
(define (node l)
	(cons (number_of l) l))

(define (is-empty-tree? t)
	(if (equal? (car t) 0) #t #f))   

(define (is-leaf? t)
	(if (equal? (car t) 'Leaf) #t #f))
	
(define (leaf-val t) (car (cdr t)))

(define (nth-child t n)
	(if (equal? n -1) (car t) (nth-child (cdr t) (- n 1))))
