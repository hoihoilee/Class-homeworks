#lang racket
(require "hw1-4.rkt")
(provide zero one not-c and-c or-c)
(provide is-zero? is-one? is-not? is-and? is-or? sub-circuit)

(define zero (leaf 0))

(define one (leaf 1))

(define (not-c c) (node (list (leaf 'not) c)))

(define (and-c c1 c2) (node (list (leaf 'and) c1 c2)))

(define (or-c c1 c2) (node (list (leaf 'or) c1 c2)))

(define (is-zero? c)
	(if (is-leaf? c)
	(if (equal? (leaf-val c) 0) #t #f) #f))

(define (is-one? c)
	(if (is-leaf? c)
	(if (equal? (leaf-val c) 1) #t #f) #f))

(define (is-not? c)
	(if (is-leaf? c) #f
	(if (equal? (leaf-val (nth-child c 0)) 'not) #t #f)))

(define (is-and? c)
	(if (is-leaf? c) #f
	(if (equal? (leaf-val (nth-child c 0)) 'and) #t #f)))

(define (is-or? c)
	(if (is-leaf? c) #f
	(if (equal? (leaf-val (nth-child c 0)) 'or) #t #f)))

(define (sub-circuit c n) (nth-child c (+ n 1)))
