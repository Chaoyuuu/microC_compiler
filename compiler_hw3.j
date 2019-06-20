.class public compiler_hw3
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 50
.limit locals 50
	ldc 6
	istore 0
label_1:
	iload 0
	ldc 1
	if_icmpgt label_2
	goto label_3
label_2:
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 0
	ldc 1
	isub
	istore 0
	goto label_1
label_3:
	return
.end method
