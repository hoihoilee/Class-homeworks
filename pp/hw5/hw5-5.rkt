#lang racket

;;; If these statements are omitted, your submission will be graded 0.

(provide equal)
(provide size)
(provide beautiful)


; You can use the definitions and functions defined in hw5-4.rkt:
; black, white, glue-array-from-tree, glue-array-from-array,
; rotate-array, neighbor-array, pprint-array, is-array?,
; glue-tree-from-tree, glue-tree-from-array, rotate-tree,
; neighbor-tree, pprint-tree, is-tree?, array-to-tree, tree-to-array,
; glue, rotate, neighbor, pprint
(require "hw5-4.rkt")


;;; interfaces
(define (equal f g) ; equal: form * form -> bool
	(if (is-array? f) (equal? f (tree-to-array g)) (equal? f (array-to-tree g))))

(define (size f) ; size: form -> int
	(define (log_2 n)
	(if (equal? n 1) 0
	(+ 1 (log_2 (/ n 2)))))
	(if (or (equal? f black) (equal? f white)) 0
	(log_2 (length (cdr (tree-to-array f))))))

(define (start i) (if (equal? i 0) '() (cons 0 (start (- i 1)))))
(define (end i) (if (equal? i 0) '() (cons 3 (end (- i 1)))))
(define (next loc)
	(define (helper l C)
	(if (null? l) '()
	(if (and (equal? (car l) 3) (equal? C 1)) (cons 0 (helper (cdr l) 1))
	(cons (+ (car l) C) (helper (cdr l) 0)))))
	(reverse (helper (reverse loc) 1)))

(define (beautiful f) ; beautiful: form -> bool
  (define (beautiful-sym f) (equal f (rotate (rotate f))))
  (define (beautiful-neighbor f)
	(define i (size f))
	(define e (end i))
	(define (helper cur_loc f)
		(let ((nei (neighbor cur_loc f)))
		(if (equal? cur_loc e) (and (> nei 1) (< nei 6))
		(if (and (> nei 1) (< nei 6)) (helper (next cur_loc) f) #f))))
	(helper (start i) f))
  (or (beautiful-sym f) (beautiful-neighbor f)))
