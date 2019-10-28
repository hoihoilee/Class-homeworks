#lang racket
(require "hw1-6.rkt")
(provide output)

(define (output c)
	(if (is-zero? c) 0
	(if (is-one? c) 1
	(if (is-not? c) (if (equal? (output (sub-circuit c 0)) 0) 1 0)
	(if (is-and? c) (* (output (sub-circuit c 0)) (output (sub-circuit c 1)))
	(if (is-or? c) (if (equal? (+ (output (sub-circuit c 0)) (output (sub-circuit c 1))) 0) 0 1)
	'null))))))
