#lang racket

(provide black)
(provide white)

(provide glue-array-from-tree)
(provide glue-array-from-array)
(provide rotate-array)
(provide neighbor-array)
(provide pprint-array)
(provide is-array?)

(provide glue-tree-from-tree)
(provide glue-tree-from-array)
(provide rotate-tree)
(provide neighbor-tree)
(provide pprint-tree)
(provide is-tree?)

(provide array-to-tree)
(provide tree-to-array)

(provide glue)
(provide rotate)
(provide neighbor)
(provide pprint)


;;; primitive tile

(define black ; black: form
  'B)
(define white ; white: form
  'W)


;;; complex tile
;
; An array tile looks like:
; (cons 'array (list row_1 row_2 ... row_n)),
; for each row_i = (list cell_i1 ... cell_in).
;
; Examples:
; 1.
; (cons 'array (list (list 'B 'B) (list 'W 'W)))
; BB
; WW
;
; 2.
; (cons 'array (list (list 'B 'B 'B 'B) (list 'B 'B 'B 'B) (list 'W 'W 'B 'B) (list 'W 'W 'B 'B)))
; BBBB
; BBBB
; WWBB
; WWBB
;
;
; An tree tile looks like:
; (cons 'tree (list subtree_nw subtree_ne subtree_se subtree_sw)).
;
; Examples:
; 1.
; (cons 'tree (list 'B 'B 'W 'B))
; BB
; BW
;
; 2.
; (cons 'tree (list (list 'B 'B 'B 'W) (list 'B 'B 'W 'B) (list 'B 'W 'B 'B) (list 'W 'B 'B 'B)))
; BBBB
; WBBW
; WBBW
; BBBB
;
; See hw5-4-selfgrader.rkt for more details on grading array and tree representation.

(define (glue-array-from-tree nw ne se sw) ; glue-array-from-tree: form * form * form * form -> form
	(tree-to-array (glue-tree-from-tree nw ne se sw)))

(define (glue-array-from-array nw ne se sw) ; glue-array-from-array: form * form * form * form -> form
	(define (helper nw_ ne_ se_ sw_)
        (if (or (null? se_) (null? sw_)) '()
        (if (or (null? nw_) (null? ne_)) (append (list (append (car sw_) (car se_))) (helper nw_ ne_ (cdr se_) (cdr sw_)))
        (append (list (append (car nw_) (car ne_))) (helper (cdr nw_) (cdr ne_) se_ sw_)))))
	(if (or (equal? nw black) (equal? nw white))
	(cons 'array (list (list nw ne) (list sw se)))
	(cons 'array (helper (cdr nw) (cdr ne) (cdr se) (cdr sw)))))

(define (glue-tree-from-tree nw ne se sw) ; glue-tree-from-tree: form * form * form * form -> form
	(if (or (equal? nw black) (equal? nw white))
	(cons 'tree (list nw ne se sw))
	(cons 'tree (list (cdr nw) (cdr ne) (cdr se) (cdr sw)))))

(define (glue-tree-from-array nw ne se sw) ; glue-tree-from-array: form * form * form * form -> form
	(array-to-tree (glue-array-from-array nw ne se sw)))

(define (rotate-array f) ; rotate-array: form -> form
	(tree-to-array (rotate-tree (array-to-tree f))))

(define (loc-x loc x n)
        (if (null? loc) x
        (if (or (equal? (car loc) 0) (equal? (car loc) 3)) (loc-x (cdr loc) x (/ n 2)) (loc-x (cdr loc) (+ x (/ n 2)) (/ n 2)))))

(define (loc-y loc y n)
        (if (null? loc) y
        (if (or (equal? (car loc) 0) (equal? (car loc) 1)) (loc-y (cdr loc) y (/ n 2)) (loc-y (cdr loc) (+ y (/ n 2)) (/ n 2)))))

(define (neighbor-array location f) ; neighbor-array: location * form -> int
	(define (fin l n) (if (equal? n 0) (car l) (fin (cdr l) (- n 1))))
	(define (helper x_ y_ f_) (let ((len (length f_)))
	(if (or (< x_ 0) (< y_ 0) (>= x_ len) (>= y_ len)) 0
	(if (equal? black (fin (fin f_ y_) x_)) 1 0))))
	(if (or (equal? f black) (equal? f white)) 0
	(let ((x (loc-x location 0 (length (cdr f)))) (y (loc-y location 0 (length (cdr f)))) (c_f (cdr f)))
	(+ (helper (- x 1) (- y 1) c_f) (helper x (- y 1) c_f) (helper (+ x 1) (- y 1) c_f) (helper (- x 1) y c_f) (helper (+ x 1) y c_f) (helper (- x 1) (+ y 1) c_f) (helper x (+ y 1) c_f) (helper (+ x 1) (+ y 1) c_f)))))

; In the document, it is said to have type form -> void, but implement
; as form -> string.
; Read hw5-4-selfgrader.rkt for formatting.
(define (pprint-array f) ; pprint-array: form -> string
	(define (helper1 l)
	(if (null? l) "\n" (if (equal? black (car l)) (string-append "B" (helper1 (cdr l))) (string-append "W" (helper1 (cdr l))))))
	(define (helper2 f_)
	(if (null? f_) "" (string-append (helper1 (car f_)) (helper2 (cdr f_)))))
	(if (equal? f black) "B\n" (if (equal? f white) "W\n"
	(helper2 (cdr f)))))

(define (is-array? f) ; is-array?: form -> bool
  (cond [(equal? 'B f) #t]
        [(equal? 'W f) #t]
        [(equal? 'array (car f)) #t]
        [else #f]))

;;; implementation with tree

(define (rotate-tree f) ; rotate-tree: form -> form
	(define (helper f_)
        (let ((nw (car f_)) (ne (cadr f_)) (se (caddr f_)) (sw (cadddr f_)))
        (if (or (equal? nw black) (equal? nw white)) (list sw nw ne se)
        (list (helper sw) (helper nw) (helper ne) (helper se)))))
	(if (or (equal? f black) (equal? f white)) f
	(cons 'tree (helper (cdr f)))))

(define (neighbor-tree loc f) ; neighbor-tree: location * form -> int
	(neighbor-array loc (tree-to-array f)))
; In the document, it is said to have type form -> void, but implement
; as form -> string.
(define (pprint-tree f) ; pprint-tree: form -> string
	(pprint-array (tree-to-array f)))

(define (is-tree? f) ; is-tree?: form -> bool
  (cond [(equal? 'B f) #t]
        [(equal? 'W f) #t]
        [(equal? 'tree (car f)) #t]
        [else #f]))

;;; conversions 
(define (half1 l)
	(define (helper l_ n)
	(if (equal? n 1) (list (car l_))
	(cons (car l_) (helper (cdr l_) (- n 1)))))
	(helper l (/ (length l) 2)))

(define (half2 l)
	(define (helper l_ n)
	(if (equal? n 1) (cdr l_)
	(helper (cdr l_) (- n 1))))
	(helper l (/ (length l) 2)))

(define (w_m l)
	(if (null? l) '()
	(cons (half1 (car l)) (w_m (cdr l)))))

(define (e_m l)
	(if (null? l) '()
	(cons (half2 (car l)) (e_m (cdr l)))))
	
(define (array-to-tree f) ; array-to-tree: form -> form
	(define (helper f_)
        (if (equal? (length f_) 2) (append (car f_) (list (cadr (cadr f_)) (car (cadr f_))))
        (list (helper (w_m (half1 f_))) (helper (e_m (half1 f_))) (helper (e_m (half2 f_))) (helper (w_m (half2 f_))))))
	(if (or (equal? f black) (equal? f white) (is-tree? f)) f
        (cons 'tree (helper (cdr f)))))

(define (tree-to-array f) ; tree-to-array: form -> form
	(define (helper f_)
	(if (or (equal? (car f_) black) (equal? (car f_) white)) (list (half1 f_) (list (cadddr f_) (caddr f_)))
	(cdr (glue-array-from-array (cons 'array (helper (car f_))) (cons 'array (helper (cadr f_))) (cons 'array (helper (caddr f_))) (cons 'array (helper (cadddr f_)))))))
	(if (or (equal? f black) (equal? f white) (is-array? f)) f
	(cons 'array (helper (cdr f)))))

;;; interfaces

(define (glue nw ne se sw) ; glue: form * form * form * form -> form
	(if (is-array? nw) (glue-array-from-array nw (tree-to-array ne) (tree-to-array se) (tree-to-array sw))
	(glue-tree-from-tree nw (array-to-tree ne) (array-to-tree se) (array-to-tree sw))))

(define (rotate f) ; rotate: form -> form
  (if (is-array? f)
      (rotate-array f)
      (rotate-tree f)))

(define (neighbor loc f) ; neighbor: location * form -> int
  (if (is-array? f)
      (neighbor-array loc f)
      (neighbor-tree loc f)))

; In the document, it is said to have type form -> void, but implement
; as form -> string.
(define (pprint f) ; pprint: form -> string
  (if (is-array? f)
      (pprint-array f)
      (pprint-tree f)))
