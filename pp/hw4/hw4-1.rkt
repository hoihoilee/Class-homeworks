#lang racket

(provide vlencode)

(define (vlencode frequencies)
	(let ((tree_list (make_tree_list frequencies)))
	(if (equal? (length tree_list) 0) '()
	(if (equal? (length tree_list) 1) (make_code (car tree_list) '(0))
	(make_code (make_tree tree_list) '())))))
	
(define (make_tree_list input) ;input is list. The number of this list is reducing by 'cdr'. when list becomes null function ends
	(if (null? input) '()
	(let ((str (caar input)) (frq (cdar input)))
	(if (equal? frq 0) (make_tree_list (cdr input))
	(cons (leaf str frq) (make_tree_list (cdr input))))))) ;input->(cdr input)->(cdr (cdr input))-> ... -> null (end)

(define (make_code tree code) ;this function traverse the tree (postorder traversal). when search the leaf node, function ends
	(if (isleaf? tree) (list (cons (leafstr tree) code))
	(append (make_code (leftsub tree) (append code (list 0))) (make_code (rightsub tree) (append code (list 1))))))
	;tree->lefttree->...->leaf, ->righttree->....->leaf (end)

(define (find_min tree_list min_tree) ;tree_list is list. # of list is reducing by 'cdr'. when list becomes null function ends
	(if (null? tree_list) min_tree
	(let ((frq (rootval (car tree_list))) (min_val (rootval min_tree)))
	(if (< frq min_val) (find_min (cdr tree_list) (car tree_list))
 	(find_min (cdr tree_list) min_tree))))) ;tree_list->(cdr tree_list)->(cdr (cdr tree_list))->...->null (end)

(define (make_tree tree_list) ;tree_list is list. # of list is reducing by 'node' function (it makes tree which has left sub tree and right sub tree as childnode). when list has only one element, function ends
	(if (equal? (length tree_list) 1) (car tree_list)
	(let ((min_tree1 (find_min tree_list (car tree_list)))
		(min_tree2 (find_min (remove_tree tree_list (find_min tree_list (car tree_list))) (car (remove_tree tree_list (find_min tree_list (car tree_list)))))))
	(make_tree (cons (node min_tree1 (+ (rootval min_tree1) (rootval min_tree2)) min_tree2) (remove_tree (remove_tree tree_list min_tree1) min_tree2)))))) ;(tree1, tree2, .., treen)->(tree1, (tree2, tree3), ...,treen)->...(tree) (end)

(define (remove_tree tree_list tree) ;tree_list is list. if it finds the tree, function end. if not, check next element.
	(if (equal? tree (car tree_list)) (cdr tree_list)
	(remove_tree (append (cdr tree_list) (list (car tree_list))) tree)))
	;ex)when find tree2 : (tree1, tree2, ..., treen) -> (tree2, tree3, ...,treen, tree1) -> find tree2 (end)
		  
;  The output of vlencode should follow the following form.
;  The exact code for each word can be different from this example,
;   but the length of the code for each word should be the same.
;  
;   (define frequencies (list (cons "a" 5) (cons "b" 1) (cons "c" 1) (cons "d" 1)))
;   (vlencode frequencies) =
;     (list (cons "a" (list 0)) (cons "b" (list 1 0)) (cons "c" (list 1 1 0)) (cons "d" (list 1 1 1)))
;
;   (define frequencies (list (cons "a" 3) (cons "b" 4) (cons "c" 5) (cons "d" 6)))
;   (vlencode frequencies) =
;     (list (cons "a" (list 0 0)) (cons "b" (list 0 1)) (cons "c" (list 1 0)) (cons "d" (list 1 1)))
;
;   (define frequencies (list (cons "a" 3) (cons "b" 4) (cons "c" 5) (cons "d" 6) (cons "e" 0)))
;   (vlencode frequencies) =
;     (list (cons "a" (list 0 0)) (cons "b" (list 0 1)) (cons "c" (list 1 0)) (cons "d" (list 1 1)))
;
; You may need the following tree interface (but not mandatory.)

(define (leaf str val) ; leaf: string * value -> tree
	(list str val))

(define (node lsub val rsub) ; node: tree * value * tree -> tree
	(list lsub val rsub))

(define (isleaf? tree) ; isleaf?: tree -> bool
	(if (equal? (length tree) 2) #t #f))

(define (leftsub tree) ; leftsub: tree -> tree
	(car tree))

(define (rightsub tree) ; rightsub: tree -> tree
	(caddr tree))

(define (leafval tree) ; leafval: tree -> value
	(cadr tree))

(define (leafstr tree) ; leftstr: tree -> string
	(car tree))

(define (rootval tree) ; rootval: tree -> value
	(cadr tree))
