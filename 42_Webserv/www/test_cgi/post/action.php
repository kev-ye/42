<html>
<body>
    <p>Welcome: <?php echo $_POST['name']; ?></p>
    <p>Your email address is: <?php echo $_POST['email']; ?></p>

	<?php echo $HTTP_RAW_POST_DAT ?>
</body>
</html>