# Unvalidated_redirects_and_forwards 

## Description

Unvalidated redirects and forwards are possible when a web application accepts untrusted input that could cause the web application to redirect the request to a URL contained within untrusted input. By modifying untrusted URL input to a malicious site, an attacker may successfully launch a phishing scam and steal user credentials.

## Try_modify_redirection_parameter

    When i inspect the web page, i see some redirection url on social logo.
    So i put a invalid parameter to this redirect url that i get a flag: b9e775a0291fed784a2d9680fcfad7edd6b8cdf87648da647aaf4bba288bcab3

## Solutions

    - Avoid using redirects and forwards.
    - If used, do not allow the URL as user input for the destination.
    - If user input can’t be avoided, ensure that the supplied value is valid, appropriate for the application, and is authorized for the user
    - Sanitize input by creating a list of trusted URLs