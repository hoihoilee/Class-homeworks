#lang racket

(require "sum.rkt")
; Do not assume anything about 'sum'.
; Use the provided functions (inl, inr, case-sum) only.

(provide bstree-make bstree-add-elmt bstree-del-elmt bstree-find-elmt)

(define (bstree-make) (mcons '() (mcons '() '()))) ;(mcons (cons key,value), (mcons lst,rst))

(define (bstree-add-elmt t k v)
	(if (null? (mcar t)) (let ((x1 (set-mcar! t (cons k v))) (x2 (set-mcdr! t (mcons (bstree-make) (bstree-make))))) #f)
	(let ((r_key (car (mcar t))))
	(if (> r_key k) (bstree-add-elmt (mcar (mcdr t)) k v)
	(if (< r_key k) (bstree-add-elmt (mcdr (mcdr t)) k v)
	(let ((x (set-mcar! t (cons k v)))) #t))))))
	
(define (bstree-del-elmt t k)
	(define (rmv-min t)
		(let ((lst (mcar (mcdr t))) (rst (mcdr (mcdr t))))
		(if (equal? lst (bstree-make))
		(if (equal? rst (bstree-make)) (let ((kv (mcar t)) (x1 (set-mcar! t '())) (x2 (set-mcdr! t (mcons '() '())))) kv)
		(let ((kv (mcar t)) (x1 (set-mcar! t (mcar rst))) (x2 (set-mcdr! t (mcdr rst)))) kv))
		(rmv-min lst))))
	
	(if (null? (mcar t)) #f
	(let ((r_key (car (mcar t))) (lst (mcar (mcdr t))) (rst (mcdr (mcdr t))))
	(if (> r_key k) (bstree-del-elmt lst k)
	(if (< r_key k) (bstree-del-elmt rst k)
	(if (and (equal? lst (bstree-make)) (equal? rst (bstree-make))) (let ((x1 (set-mcar! t '())) (x2 (set-mcdr! t (mcons '() '())))) #t)
	(if (and (not (equal? lst (bstree-make))) (equal? rst (bstree-make))) (let ((x1 (set-mcar! t (mcar lst))) (x2 (set-mcdr! t (mcdr lst)))) #t)
	(if (and (equal? lst (bstree-make)) (not (equal? rst (bstree-make)))) (let ((x1 (set-mcar! t (mcar rst))) (x2 (set-mcdr! t (mcdr rst)))) #t)
	(let ((x1 (set-mcar! t (rmv-min rst)))) #t)))))))))

(define (bstree-find-elmt t k)
	(if (null? (mcar t)) (inr 'null)
	(let ((r_key (car (mcar t))) (lst (mcar (mcdr t))) (rst (mcdr (mcdr t))))
	(if (> r_key k) (bstree-find-elmt lst k)
	(if (< r_key k) (bstree-find-elmt rst k)
	(inl (cdr (mcar t))))))))
