#lang racket

(provide empty link case-list)

(define empty (list 0))

(define (link v l) (cons (+ (car l) 1) (cons v (cdr l))))

(define (case-list f1 f2 l)
	(if (equal? (car l) 0) (f1 l) (f2 (cadr l) (cons (- (car l) 1) (cddr l)))))
