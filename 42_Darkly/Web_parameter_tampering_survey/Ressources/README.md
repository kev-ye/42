# Web_parameter_tampering

## Description

The Web Parameter Tampering attack is based on the manipulation of parameters exchanged between client and server in order to modify application data, such as user credentials and permissions, price and quantity of products, etc. Usually, this information is stored in cookies, hidden form fields, or URL Query Strings, and is used to increase application functionality and control.

## Sensitive_data_in_page_inspect

    In survey page, i found a grade use a select element with 1-10 options values.
    So i try modify some invalid value and finally i get a flag: 03a944b434d5baff05f46c4bede5792551a2595574bcafc9a6e25f67c382ccaa

## Solutions

    - Using regex to limit or validate data
    - Server-side validation compared with all inputs