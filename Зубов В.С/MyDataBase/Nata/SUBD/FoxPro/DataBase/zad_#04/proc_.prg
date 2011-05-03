&& файл с процедурами
&& Процедура P_Trace
&&	Входные данные: A - матрица NxN
PROCEDURE P_Trace
 PARAM A,N,I,J
 	DECLARE T[N,N]
	FOR I=1 TO N
		FOR J=1 TO N
			T[I,J]=A[J,I]
		ENDFOR
	ENDFOR
	FOR I=1 TO N
		FOR J=1 TO N
			A[I,J]=T[I,J]
		ENDFOR
	ENDFOR
