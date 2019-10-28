#lang racket

(require "hw5-1.rkt")
(require "hw5-2.rkt")

(provide is-empty? fst rest length nth-elmt map reduce)

(define (is-empty? #|t_list->bool|# l #|t_list|# )
	(case-list (lambda (u) #t) #|unit->bool|# (lambda (h t) #f) #|t,t_list->bool|# l #|t_list|# ) #|bool|# )

(define (fst #|t_list->t+unit|# l #|t_list|# )
	(case-list (lambda (u) (inr '())) #|unit->t+unit|# (lambda (h t) (inl h)) #|t,t_list->t+unit|# l #|t_list|# ) #|t+unit|# )

(define (rest #|t_list->t_list+unit|# l #|t_list|# )
	(case-list (lambda (u) (inr '())) #|unit->t_list+unit|# (lambda (h t) (inl t)) #|t,t_list->t_list+unit|# l #|t_list|# ) #|t_list+unit|# )

(define (length #|t_list->int|# l #|t_list|# )
	(case-list (lambda (u) 0) #|unit->int|# (lambda (h t) (+ 1 (length t))) #|t,t_list->int|# l #|t_list|# ) #|int|# )

(define (nth-elmt #|t_list,int->t+unit|# l #|t_list|# i #|int|# )
	(case-list (lambda (u) (inr '())) #|unit->t+unit|# (lambda (h t) (if (equal? i 0) (inl h) #|t+unit|# (nth-elmt t (- i 1)) #|t+unit|# )) #|t+unit|# l #|t_list|# ) #|t+unit|# )

(define (map #||t->s|,t_list->s_list|# f #|t->s|# l #|t_list|# )
	(case-list (lambda (u) empty) #|unit->s_list|# (lambda (h t) (link (f h) #|s|# (map f t) #|s_list|# ) #|s_list|# ) #|t,t_list->s_list|# l #|t_list|# ) #|s_list|# )

(define (reduce #|t_list,|t,s->s|,s->s|# l #|t_list|# f #|t,s->s|# s #|s|# )
	(case-list (lambda (u) s) #|unit->s|# (lambda (h t) (reduce t f (f h s))) #|t,t_list->s|# l #|t_list|# ) #|s|# )
