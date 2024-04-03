# Broken_Access_Control

## Description

Access control enforces policy such that users cannot act outside of their intended permissions. Failures typically lead to unauthorized information disclosure, modification, or destruction of all data or performing a business function outside the user's limits.

## .hidden

    With the /robots.txt, we have "/.hidden" and "whatever/", after access to /.hidden, we can see many path with random name, and which path we have a README file contain some troll information.
    So i run a sript to catch every README file content.
    Finally i get a flag: 99dde1d35d1fdd283924d84e6d9f1d820.

## Solution

    - Except for public resources, deny by default.
    - Disable web server directory listing and ensure file metadata (e.g., .git) and backup files are not present within web roots.