# Cross-Site_Request_Forgery

## Description

Cross-Site Request Forgery (CSRF) is a type of attack that occurs when a malicious web site, email, blog, instant message, or program causes a user's web browser to perform an unwanted action on a trusted site when the user is authenticated. A CSRF attack works because browser requests automatically include all cookies including session cookies. Therefore, if the user is authenticated to the site, the site cannot distinguish between legitimate authorized requests and forged authenticated requests. This attack is thwarted when proper Authorization is used, which implies that a challenge-response mechanism is required that verifies the identity and authority of the requester.

## BornToSec

    At bottom of the site, we can click on the "BornToSec". After access to this page, and if we inspect it, we can see a big comment with some utils information:
    - "You must cumming from : "https://www.nsa.gov/" to go to the next step"
    - "Let's use this browser : "ft_bornToSec". It will help you a lot."

    So we need do change the Referrer and the user-agent.
    After using url with the new referrer and user-agent. I get the flag: f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Solutions

    - Add whitelist for referer and user-agent
    - Add a token verify or a verification code