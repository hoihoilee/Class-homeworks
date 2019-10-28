#lang racket
; not for execution
; write a type of each expression

(define (sigma #|int,int->int|# lower #|int|# upper #|int|# )
  (lambda (f)
    (define (loop #|int->int|# n #|int|# )
      (if (> n upper) #|bool|# 0 #|int|#
          (+ (f n) #|int|# (loop (+ n 1) #|int|# )) #|int|# ))
    (loop lower) #|int|#
    ) #|int|#
  )

(define (generic-sum #|seq1,seq2,|seq1->seq3|,|seq1,seq2->bool|,seq4,|seq3,seq4->seq4|,|seq1->seq1|->seq4|# lower #|seq1|# upper #|seq2|# f #|seq1->seq3|# larger #|seq1,seq2->bool|# base #|seq4|# op #|seq3,seq4->seq4|# inc #|seq1->seq1|# )
  (if (larger lower upper) #|bool|# base #|seq4|#
      (op (f lower) #|seq3|#
          (generic-sum (inc lower) upper f larger base op inc) #|seq4|# )
      ) #|seq4|#
  )

(define (map #||ele1->ele2|,ele1_list->ele2_list|# f #|ele1->ele2|# l #|ele1_list|# )
  (if (null? l) #|bool|# '() #|ele2_list|#
      (cons (f (car l) #|ele1|# ) #|ele2|# (map f (cdr l) #|ele1_list|# ) #|ele2_list|# ) #|ele2_list|#
      ) #|ele2_list|#
  )

(define (reduce #|ele2_list,|ele2,ele3->ele3|,ele3->ele3|# l #|ele2_list|# op #|ele2,ele3->ele3|# init #|ele3|# )
  (if (null? l) #|bool|# init #|ele3|#
      (op (car l) #|ele2|# (reduce (cdr l) #|ele2_list|# op init) #|ele3|#) #|ele3|#
      ) #|ele3|#
  )

(define (map-reduce #||ele1->ele2|,ele1_list,|ele2,ele3->ele3|,ele3->ele3|# f #|ele1->ele2|# l #|ele1_list|# op #|ele2,ele3->ele3|# init #|ele3|# )
  (reduce (map f l) #ele2_list|# op init) #|ele3|#
  )
