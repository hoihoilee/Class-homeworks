#lang racket

(require "hw3-2-library.rkt")

(provide maze-check)

(define (maze-check maze start end)
	(if (same-room? start end) #t
	(if (or (null? (can-enter start maze)) (null? (can-enter end maze))) #f
	(route-check (can-enter start maze) (add-element start empty-set) maze end))))

(define (route-check r_list r_set maze end)
	(if (null? r_list) #f
	(let ((start (car r_list)))
	(if (same-room? start end) #t
	(if (is-member? start r_set) (route-check (cdr r_list) r_set maze end)
	(if (route-check (can-enter start maze) (add-element start r_set) maze end) #t
	(route-check (cdr r_list) (history (can-enter start maze) (add-element start r_set) maze) maze end)))))))

(define (history r_list r_set maze)
	(if (null? r_list) r_set
	(if (is-member? (car r_list) r_set) (history (cdr r_list) r_set maze)
	(history (cdr r_list) (history (can-enter (car r_list) maze) (add-element (car r_list) r_set) maze) maze))))
