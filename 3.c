#!/bin/bash
find $1 -perm $2 -exec [chmod $3'{}'\;]
