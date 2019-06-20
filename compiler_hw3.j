.class public compiler_hw3
.super java/lang/Object
.field public static a I = 100
.field public static b I = 20
.method public static foo(II)I
.limit stack 50
.limit locals 50
	iload 0
	iload 1
	iadd
	istore 2
	iload 2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 0
	ireturn
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 50
.limit locals 50
	ldc 8
	istore 0
	getstatic compiler_hw3/a I
	getstatic compiler_hw3/b I
	invokestatic compiler_hw3/foo(II)I
	istore 0
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
