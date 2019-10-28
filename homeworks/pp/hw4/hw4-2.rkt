#lang racket
; We auto-grade only "react" function; other functions are not
; auto-graded. However, S, K, I, v, and a are required for
; grading. See hw4-2-grade.rkt for more information.
(provide react S K I v a)
; Implement react. 
;
; In the document, react has the type solution -> void.
; However, implement react: solution -> string for ease of grading.
; Return the string of the given solution printed by pprint.
;
; See hw4-2-grade.rkt for more information on what the returned string should look like.
; In short,
; S prints "S";
; K prints "K";
; I prints "I";
; variable x prints "x";
; tuple (E F) prints "(" + E + " " + F + ")".

(define (react e)
	(pprint (if_react e)))

(define (if_react e)
	(if (or (isS? e) (isK? e) (isI? e) (isv? e)) e
	(if (isI? (al e)) (if_react (ar e))
	(if (isa? (al e)) (if (isK? (al (al e))) (if_react (ar (al e)))
	(if (isa? (al (al e))) (if (isS? (al (al (al e)))) (if_react (a (a (ar (al (al e))) (ar e)) (a (ar (al e)) (ar e)))) (else_react e)) (else_react e))) (else_react e)))))

(define (else_react e)
	(if (equal? e (a (if_react (al e)) (if_react (ar e)))) e
	(if_react (a (if_react (al e)) (if_react (ar e))))))

(define S (list 'S)) ; S: solution
	
(define K (list 'K)); K: solution

(define I (list 'I)); I: solution

(define (v str) (list str)) ; v: string -> solution

(define (a lhs rhs) (list lhs rhs)) ; a: solution * solution -> solution

; You may need the following tree interface.

(define (isS? e) ; isS?: solution -> bool
	(if (equal? (car e) 'S) #t #f))
(define (isK? e) ; isK?: solution -> bool
	(if (equal? (car e) 'K) #t #f))
(define (isI? e) ; isI?: solution -> bool
	(if (equal? (car e) 'I) #t #f))
(define (isv? e) ; isv?: solution -> bool
	(if (equal? (length e) 1)
	(if (or (isS? e) (isK? e) (isI? e)) #f #t) #f))
(define (isa? e) ; isa?: solution -> bool
	(if (equal? (length e) 1) #f #t))
(define (var e) ; var: solution -> string
	(car e))
(define (al e) ; al: solution -> solution
	(car e))
(define (ar e) ; ar: solution -> solution
	(cadr e))
(define (pprint e) ; pprint: solution -> string
	(if (isS? e) "S"
	(if (isK? e) "K"
	(if (isI? e) "I"
	(if (isv? e) (var e)
	(string-append "(" (pprint (al e)) " " (pprint (ar e)) ")"))))))
