# Unrestricted_file_upload

## Description

Uploaded files represent a significant risk to applications. The first step in many attacks is to get some code to the system to be attacked. Then the attack only needs to find a way to get the code executed. Using a file upload helps the attacker accomplish the first step.

## Test_upload_file

    I'm trying some upload tests. But we can only upload a JPEG image files.
    So i tried renaming the txt file to jpg extension, and that's success!
    I think the website only check "Content-Type: image/jpeg" in headers.

## Try_upload_the_file_by_modify_headers

    I re-upload a php file and modify the headers: (in Mozilla Firefox)
    "Content-Type: application/x-php" -> "Content-Type: image/jpeg".
    And finally i get the Flag: 46910d9ce35b385885a9f7e2b336249d622f29b267a1771fbacf52133beddba8

## Solutions

    - Allow Listing File Extensions
    - Using a File Type Detector
    - Check if is a file adapted