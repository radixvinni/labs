<?php
	session_start();
	// œ‡‡ÏÂÚ˚
	$guest_access_allow = true;
	$allowed_types_users = array(
        '/\.txt$/i' => 'text',
        '/\.gif$/i' => 'image',
        '/\.(jpg|jpeg|jpe)$/i' => 'image',
		'/\.png$/i' => 'image',
        '/\.html?$/i' => 'html'
    );
	$skip_files=array('.', 'index.html', '_access.txt');
	
	$users = file('inc/users.txt');
	if($guest_access_allow) $users=array_merge(array('guest::0:0:√ÓÒÚ¸:/guest:'),$users);
	
	$action=$_REQUEST['action'];
	if(!isset($_SESSION['user'])) $_SESSION['user']=0;
	$user=$_SESSION['user'];
	$allowed_types=$allowed_types_users;
	
	if ($user || $guest_access_allow)
	{	
		header("Content-Type: text/xml");
		switch($action){
		case "login":login();break;
		case "logout":logout();break;
		case "file":statfile();break;
		case "reg":reg();break;
		case "list":
		default:listdir();break;
		}
	}
	else
	{	
		login();
	}
	
	function listdir()
	{
		global $users, $user, $skip_files, $allowed_types;
		$sizes = array(" ·‡ÈÚ", "  ¡", " Ã¡", " √¡", " “¡", " œ¡", " ≈¡", " «¡");
		$curr_dir=preg_replace('/\/?([^\/\\\]*)\/\.\./','',$_REQUEST['dir']);
		list($user, $pass, $uid, $gid, $extra, $home_dir) = explode(":", $users[$user]);
		$ref_dir="data".$home_dir.$curr_dir;
		$stat = array_combine(array_map('trim', file("inc/statkeys.txt")), array_map('trim',file("inc/statvals.txt")));
			$stat[$ref_dir]++;
			file_put_contents("inc/statkeys.txt", implode("\n", array_keys($stat)));
			file_put_contents("inc/statvals.txt", implode("\n", array_values($stat)));
		
		$wd=opendir($ref_dir);
		while ($w=readdir($wd))
		{	if(!in_array($w,$skip_files))
			$dir[]=$w;
		}
		closedir($wd);
		
		print "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n";
		print "<page action=\"listdir\" dir=\"{$curr_dir}\" user=\"{$user}\" uid=\"{$uid}\" gid=\"{$gid}\" extra=\"{$extra}\" home=\"{$home_dir}\">";
		foreach($dir as $w)
		{	$file=$ref_dir.'/'.$w;
			if (is_dir($file)) $type="directory";
			if (is_file($file)) 
				foreach($allowed_types as $k => $v)
					if(preg_match($k,$w)>0) $type=$v;
			$size=filesize($file);
			$size=$size?(round($size/pow(1024, ($i = floor(log($size, 1024)))), $i > 1 ? 2 : 0) . $sizes[$i]):"";
			print "<item name=\"{$w}\" type=\"{$type}\" href=\"index.php?action=file&amp;file={$file}\" file=\"{$curr_dir}/{$w}\" size=\"{$size}\" stat=\"{$stat[$file]}\"></item>";
		}
		print "</page>";
		
	}
	
	function login()
	{
		global $users;
		$error=0;
		if (!empty($_REQUEST['login']))
		{	$error=1;
			foreach($users as $k=>$v)
			{	list($user, $pass) = explode(":", $v);
				if ($_REQUEST['login']==$user && MD5($_REQUEST['password'])==$pass)
				{	$_SESSION['user']=$k;
					$error=0;
					header("Location: index.php");
					return;
				}
			}
		}
		$login=htmlspecialchars($_REQUEST['login']);
		print "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n";
		print "<page action=\"login\" error=\"{$error}\" login=\"{$login}\" />";
	}
	function logout()
	{
		session_destroy();
		header("Location: index.php");
	}
	function statfile()
	{
		$file=$_REQUEST['file'];
			$stat = array_combine(array_map('trim', file("inc/statkeys.txt")), array_map('trim', file("inc/statvals.txt")));
			$stat[$file]++;
			file_put_contents("inc/statkeys.txt", implode("\n", array_keys($stat)));
			file_put_contents("inc/statvals.txt", implode("\n", array_values($stat)));
		header("Location: {$file}");
	}
	function reg()
	{
		print "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n";
		global $users;
		$error=0;
		$password=htmlspecialchars($_REQUEST['password']);
		$login=htmlspecialchars($_REQUEST['login']);
		$home=htmlspecialchars($_REQUEST['home']);
		$group=htmlspecialchars($_REQUEST['group']);
				
		if (!empty($_REQUEST['login']))
		{	foreach($users as $k=>$v)
			{	list($user, $pass) = explode(":", $v);
				if ($_REQUEST['login']==$user){
					$error=1;
				}
			}
			if($error==0){
				$f=implode(':',array($login,md5($password),count($users),$group,$login,$home,""));
				$h=fopen("inc\\users.txt", "a+");
				fwrite($h,"\r\n".$f);
				fclose($h);
				$error=2;
			}
		}
		print "<page action=\"reg\" error=\"{$error}\" login=\"{$login}\" home=\"{$home}\" group=\"{$group}\" />";
	}
?>