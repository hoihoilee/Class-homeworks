#lang racket

(provide myeval)

; Read the instruction of document carefully,
; and then write code according to it.

; This `myeval` function should mimic the behavior of `eval`,
; which is a built-in function of Racket.

; You should raise exceptions for irregular situations.
; The exception message doesn't have to be the same as `eval`,
; but the message should contain useful information.

(define null ''())

(define (is_member? e l) (if (null? l) #f (if (equal? e (caar l)) #t (is_member? e (cdr l)))))

(define (get_v e l) (if (equal? e (caar l)) (cdar l) (get_v e (cdr l))))

(define (if_v in v_list)
	(if (not (equal? (length in) 3)) (raise "Invalid expression")
	(let ((con (ev (car in) v_list)) (t (ev (cadr in) v_list)) (f (ev (caddr in) v_list)))
	(if (not (boolean? con)) (raise "Invalid expression")
	(if con t f)))))

(define (cons_v in v_list)
	(if (not (equal? (length in) 2)) (raise "Invalid expression")
	(let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
	(if (not (and (or (pair? lft) (null? lft) (number? lft) (boolean? lft)) (or (pair? rgh) (null? rgh) (number? rgh) (boolean? rgh)))) (raise "Invalid expression")
	(cons lft rgh)))))

(define (car_v in v_list)
	(if (not (equal? (length in) 1)) (raise "Invalid expression")
	(let ((lst (ev (car in) v_list)))
	(if (not (pair? lst)) (raise "Invalid expression")
	(car lst)))))

(define (cdr_v in v_list)
	(if (not (equal? (length in) 1)) (raise "Invalid expression")
	(let ((lst (ev (car in) v_list)))
	(if (not (pair? lst)) (raise "Invalid expression")
	(cdr lst)))))

(define (lambda_v in v_list) '<procedure>)

(define (let_v in v_list)
	(define (newv_list lst save)
		(if (null? lst) save
		(let ((f_ (car lst))) (if (not (equal? (length f_) 2)) (raise "Invalid expression")
		(newv_list (cdr lst) (cons (cons (car f_) (ev (cadr f_) v_list)) save))))))
	(if (not (equal? (length in) 2)) (raise "Invalid expression")
	(ev (cadr in) (append (newv_list (car in) '()) v_list))))

(define (letrec_v in v_list) (let_v in v_list))

(define (plus_v in v_list)
	(if (not (equal? (length in) 2)) (raise "Invalid expression")
	(let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
	(if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
	(+ lft rgh)))))

(define (minus_v in v_list)
        (if (not (equal? (length in) 2)) (raise "Invalid expression")
        (let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
        (if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
        (- lft rgh)))))

(define (multi_v in v_list)
        (if (not (equal? (length in) 2)) (raise "Invalid expression")
        (let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
        (if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
        (* lft rgh)))))

(define (equal_v in v_list)
        (if (not (equal? (length in) 2)) (raise "Invalid expression")
        (let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
        (if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
	(= lft rgh)))))

(define (less_v in v_list)
	(if (not (equal? (length in) 2)) (raise "Invalid expression")
	(let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
	(if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
	(< lft rgh)))))

(define (great_v in v_list)
        (if (not (equal? (length in) 2)) (raise "Invalid expression")
        (let ((lft (ev (car in) v_list)) (rgh (ev (cadr in) v_list)))
        (if (not (and (number? lft) (number? rgh))) (raise "Invalid expression")
        (> lft rgh)))))

(define (app_v cmd in v_list)
	(define (newv_list lst1 lst2 save)
		(if (null? lst1) save (newv_list (cdr lst1) (cdr lst2) (cons (cons (car lst1) (ev (car lst2) v_list)) save))))
	(if (not (equal? (length (cadr cmd)) (length in))) (raise "Invalid expression")
	(ev (caddr cmd) (append (newv_list (cadr cmd) in '()) v_list))))
			
(define (ev e v_list)
	(if (or (null? e) (equal? null e)) '()
	(if (or (number? e) (boolean? e)) e
	(if (is_member? e v_list) (get_v e v_list)
	(if (not (pair? e)) (raise "Invalid expression")
	(let ((cmd (car e)) (in (cdr e)))
	(if (equal? cmd 'if) (if_v in v_list)
	(if (equal? cmd 'cons) (cons_v in v_list)
	(if (equal? cmd 'car) (car_v in v_list)
	(if (equal? cmd 'cdr) (cdr_v in v_list)
	(if (equal? cmd 'lambda) (lambda_v in v_list)
	(if (equal? cmd 'let) (let_v in v_list)
	(if (equal? cmd 'letrec) (letrec_v in v_list)
	(if (equal? cmd '+) (plus_v in v_list)
	(if (equal? cmd '-) (minus_v in v_list)
	(if (equal? cmd '*) (multi_v in v_list)
	(if (equal? cmd '=) (equal_v in v_list)
	(if (equal? cmd '<) (less_v in v_list)
	(if (equal? cmd '>) (great_v in v_list)
	(if (equal? (car cmd) 'lambda) (app_v cmd in v_list)
	(raise "Invalid expression")))))))))))))))))))))

(define (myeval e) (ev e '()))
