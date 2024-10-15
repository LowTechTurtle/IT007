#!/bin/bash

read -p "Nhap tuoi: " age

if ! [[ "$age" =~ ^[0-9]+$ ]] || [ "$age" -lt 0 ] || [ "$age" -gt 100 ]; then
    echo "Tuoi la gia tri so tu 0 den 100"
else
    if [ "$age" -lt 12 ]; then
        echo "Bạn là một đứa trẻ."
    elif [ "$age" -ge 12 ] && [ "$age" -le 18 ]; then
        echo "Bạn là một thiếu niên."
    else
        echo "Bạn là một người lớn."
    fi
fi

