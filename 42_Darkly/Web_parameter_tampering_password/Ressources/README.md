# Web_parameter_tampering

## Description

The Web Parameter Tampering attack is based on the manipulation of parameters exchanged between client and server in order to modify application data, such as user credentials and permissions, price and quantity of products, etc. Usually, this information is stored in cookies, hidden form fields, or URL Query Strings, and is used to increase application functionality and control.

## Sensitive_data_in_page_inspect

    I found some sensitive data about password forget form in page inspect.
    I see a "hidden" element, it contains a email with a maxlength=15.
    So i just trying modify the email and click on submit.
    And finally i get a flag: 1d4855f7337c0c14b6f44946872c4eb33853f40b2d54393fbe94f49f1e19bbb0

## Solutions

    - Implement Secure Password Recovery Mechanism
    - Don't stock sensitive information on front-end user-interface
    - Avoid unwanted or hidden data