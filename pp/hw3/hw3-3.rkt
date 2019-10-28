#lang racket

(require "hw3-3-library.rkt")

(provide mazeGen)

; Play around the interface of hw3-3-library.rkt.
; After executing this file, see hw3-3.ps.
; To read .ps files, you will need
;  - GhostScript: http://www.ghostscript.com/download/gsdnld.html
;  - Ghostview: http://pages.cs.wisc.edu/~ghost/gsview/

; some test code:
;(define maze1 (init-maze 4 3))
;(define maze2 (open-s 2 1 maze1))
;(maze-pp maze2)

(define (mazeGen n m)
	(let ((maze (init-maze n m)))
		(open-s (- n 1) (- m 1) (open-n 0 0 (random-open (- n 1) (- m 1) n m '() '() maze)))))

(define (random-open n m N M r_s his maze)
	(if (or (and (odd? m)
		(or (can-go? (- n 1) m N M his)
			(can-go? (- n 1) (+ m 1) N M his)
			(can-go? n (+ m 1) N M his)
			(can-go? (+ n 1) m N M his)
			(can-go? n (- m 1) N M his)
			(can-go? (- n 1) (- m 1) N M his)))
		(and (even? m)
		(or (can-go? (- n 1) m N M his)
			(can-go? n (+ m 1) N M his)
			(can-go? (+ n 1) (+ m 1) N M his)
			(can-go? (+ n 1) m N M his)
			(can-go? (+ n 1) (- m 1) N M his)
			(can-go? n (- m 1) N M his)))) ;it has way
	(let ((r (random 6)))
	(if (equal? r 0) (if (can-go? (- n 1) m N M his) (random-open (- n 1) m N M (history n m r_s) (history n m his) (open-n n m maze)) (random-open n m N M r_s his maze))
	(if (equal? r 1)
		(if (odd? m) (if (can-go? (- n 1) (+ m 1) N M his) (random-open (- n 1) (+ m 1) N M (history n m r_s) (history n m his) (open-ne n m maze)) (random-open n m N M r_s his maze))
			(if (can-go? n (+ m 1) N M his) (random-open n (+ m 1) N M (history n m r_s) (history n m his) (open-ne n m maze)) (random-open n m N M r_s his maze))) 
	(if (equal? r 2)
		(if (odd? m) (if (can-go? n (+ m 1) N M his) (random-open n (+ m 1) N M (history n m r_s) (history n m his) (open-se n m maze)) (random-open n m N M r_s his maze))
			(if (can-go? (+ n 1) (+ m 1) N M his) (random-open (+ n 1) (+ m 1) N M (history n m r_s) (history n m his) (open-se n m maze)) (random-open n m N M r_s his maze)))
	(if (equal? r 3) (if (can-go? (+ n 1) m N M his) (random-open (+ n 1) m N M (history n m r_s) (history n m his) (open-s n m maze)) (random-open n m N M r_s his maze))
	(if (equal? r 4)
		(if (odd? m) (if (can-go? n (- m 1) N M his) (random-open n (- m 1) N M (history n m r_s) (history n m his) (open-sw n m maze)) (random-open n m N M r_s his maze))
			(if (can-go? (+ n 1) (- m 1) N M his) (random-open (+ n 1) (- m 1) N M (history n m r_s) (history n m his) (open-sw n m maze)) (random-open n m N M r_s his maze)))
		(if (odd? m) (if (can-go? (- n 1) (- m 1) N M his) (random-open (- n 1) (- m 1) N M (history n m r_s) (history n m his) (open-nw n m maze)) (random-open n m N M r_s his maze))
			(if (can-go? n (- m 1) N M his) (random-open n (- m 1) N M (history n m r_s) (history n m his) (open-nw n m maze)) (random-open n m N M r_s his maze))))))))) 
	(if (null? r_s) maze
	(random-open (car (car r_s)) (car (cdr (car r_s))) N M (cdr r_s) (history n m his) maze))))

(define (history n m set)
	(cons (list n m) set))

(define (can-go? n m N M his)
	(if (or (< n 0) (< m 0) (>= n N) (>= m M)) #f ;out of range
	(if (is_visited? n m his) #f #t)))

(define (is_visited? n m his)
	(let ((pair (list n m)))
	(if (null? his) #f
	(if (equal? pair (car his)) #t
	(is_visited? n m (cdr his))))))
