package com.cybergarden.fbi

data class BoundingBox(
    val x1: Float,
    val y1: Float,
    val x2: Float,
    val y2: Float,
    val cnf: Float,
    val cls: Int,
    val clsName: String
)