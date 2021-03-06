<?php
if(!isset($_POST['submit']))
{
	//This page should not be accessed directly. Need to submit the form.
	echo "error; you need to submit the form!";
}
$name = $_POST['name'];
$visitor_email = $_POST['email'];
$message = $_POST['message'];
$session = $_POST['session_file'];

//Validate first
if(empty($name))
{
    $name = '<unknown name>';
}
if(empty($visitor_email)) 
{
    $visitor_email = '<unknown email>';
}

if(IsInjected($visitor_email))
{
    echo "Bad email value!";
    exit;
}

$email_from = 'web@bmrb.wisc.edu';//<== update the email address
$email_subject = "JavaScreen feedback";
$email_body = "You have received a new message from the user $name ($visitor_email).\n".
    "\nSession file: $session\n".
    "\nHere is the message:\n$message";
    
$to = "bmrbhelp@bmrb.wisc.edu";//<== update the email address
$headers = "From: $email_from \r\n";
$headers .= "Reply-To: $visitor_email \r\n";
//Send the email!
mail($to,$email_subject,$email_body,$headers);
//done. redirect to thank-you page.
header('Location: thank-you.html');


// Function to validate against any email injection attempts
function IsInjected($str)
{
  $injections = array('(\n+)',
              '(\r+)',
              '(\t+)',
              '(%0A+)',
              '(%0D+)',
              '(%08+)',
              '(%09+)'
              );
  $inject = join('|', $injections);
  $inject = "/$inject/i";
  if(preg_match($inject,$str))
    {
    return true;
  }
  else
    {
    return false;
  }
}
   
?> 
