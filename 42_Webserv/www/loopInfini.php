<html>
 <head>
  <title>Test PHP</title>
 </head>
 <body>
 <?php echo "CGI TEST OK !<p>"; 
 $interval=60; //minutes
 set_time_limit( 0 );
 $sleep = $interval*60-(time());

 while ( 1 ){
    if(time() != $sleep) {
      // the looping will pause on the specific time it was set to sleep
      // it will loop again once it finish sleeping.
      time_sleep_until($sleep); 
    }
    #do the routine job, trigger a php function and what not.
  }
  ?>
</body>
</html>
