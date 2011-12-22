<?php
$action=addslashes($_REQUEST['action']);
$ajax=intval($_REQUEST['ajax']);
$xml=($ajax==2);
print "<response ajax='{$ajax}' xml='{$xml}'><page action='{$action}' group='{$_SESSION['group']}' user='{$_SESSION['user']}' username='{$_SESSION['username']}'>";
switch($action){
	case "login":login();break;
	case "logout":logout();break;
	case "admin_test": if ($_SESSION['group']==1) test();break;
	case "admin_theme": if ($_SESSION['group']==1) theme();break;
	case "admin_cat": if ($_SESSION['group']==1) cat();break;
	case "admin_answer": if ($_SESSION['group']==1) answer();break;
	case "admin_question": if ($_SESSION['group']==1) question();break;
	case "admin_delete": if ($_SESSION['group']==1) delete();break;
	case "admin_sort": if ($_SESSION['group']==1) sortorder();break;
	case "admin_tt_set": if ($_SESSION['group']==1) tt_set();break;
	case "admin_tt_del": if ($_SESSION['group']==1) tt_del();break;
	case "admin_modify": if ($_SESSION['group']==1) modify();break;
	case "admin_modify_new": if ($_SESSION['group']==1) question();break;
	case "admin_modify_type": if ($_SESSION['group']==1) modify_type();break;
	case "admin_modify_correct": if ($_SESSION['group']==1) modify_correct();break;
	case "admin_save_solutions": if ($_SESSION['group']==1) save_solutions(); break;
	case "admin_test_limit": if ($_SESSION['group']==1) test_limit();break;
	case "admin_stat": if ($_SESSION['group']==1) stats();break;
	case "admin_result": if ($_SESSION['group']==1) result();break;
	case "admin_show_results": if ($_SESSION['group']==1) show_result();break;
	case "run":if(!empty($_SESSION['user'])) run();break;
	case "check":if(!empty($_SESSION['user'])) check();break;
	case "": home();break;
	default: print "Error 404. Page not found.";
}
print "</page></response>";

function home() {
	if(empty($_SESSION['user'])){
		header("Location: index.php?action=login");
		return;
	}
	if ($_SESSION['group']==1){
		print "<categories>";
		$result=mysql_query("SELECT t_theme, t_theme_name, c_category, c_category_name, count(*) AS t_count FROM lab3_question RIGHT JOIN lab3_theme ON q_theme=t_theme RIGHT JOIN lab3_category ON t_category=c_category GROUP BY t_theme,c_category ORDER BY c_sortorder,c_category, t_sortorder");
		sql_split($result,"t_theme","c_category");
		print "</categories>\n<tests>";
		$result=mysql_query("SELECT * FROM lab3_test_theme RIGHT JOIN lab3_test ON tt_test=e_test ORDER BY e_sortorder, e_test;");
		sql_split($result,"t_theme","e_test");
		print "</tests>";
		return;
	}
	$uid=$_SESSION['user'];
	sql_select(mysql_query("SELECT * FROM lab3_result LEFT JOIN lab3_test ON r_test=e_test WHERE r_user={$uid} AND r_text IS NULL"),"testing");
}
//sql.php
function sql_select($sql, $what){
	while($row=mysql_fetch_assoc($sql)){
		print "<{$what} ";
		foreach(array_keys($row) as $key) print "{$key}='{$row[$key]}' ";
		print "/>\n";	
	}
}
function sql_split($sql,$what,$by){
	$row=mysql_fetch_assoc($sql);
	$value = $row[$by];
	while($row) {
		print "<{$by} ";
		foreach(array_keys($row) as $key) print "{$key}='{$row[$key]}' ";
		print ">\n";
		while($row) {
			print "<{$what} ";
			foreach(array_keys($row) as $key) print "{$key}='{$row[$key]}' ";
			print "/>\n";
			$row=mysql_fetch_assoc($sql);
			if($row[$by]!=$value) break;
		}
		$value=$row[$by];
		print "</{$by}>\n";
	}
}

//user.php
function login() { 
		if (!empty($_REQUEST['reg']))
		{	$login=mysql_real_escape_string($_REQUEST['name']);
			$pass=mysql_real_escape_string($_REQUEST['pass']);
			$result=mysql_query("INSERT INTO lab3_user (u_name, u_password, u_extra) VALUES ('{$login}', MD5('{$pass}'), '');");
			if ($result)
			{		$_SESSION['user']=mysql_insert_id();
					$_SESSION['group']=0;
					$_SESSION['username']=$login;
					print "<message/>";
					return;
			}
			else
				print "<error/>";
			
		}
		else
		if (!empty($_REQUEST['login']))
		{	$login=mysql_real_escape_string($_REQUEST['name']);
			$pass=mysql_real_escape_string($_REQUEST['pass']);
			$result=mysql_query("SELECT * FROM lab3_user WHERE u_name='{$login}' and u_password=MD5('{$pass}')");
			if (mysql_num_rows($result) > 0)
			{		$row = mysql_fetch_assoc($result);
					$_SESSION['user']=$row['u_user'];
					$_SESSION['group']=$row['u_group'];
					$_SESSION['username']=$row['u_name'];
					header("Location: index.php");
					return;
			}
			else
				print "<error/>";
		}
		$login=htmlspecialchars($_REQUEST['name']);
		print "<login value='{$login}'/>";
}
function logout(){
	$_SESSION['user']='';
	$_SESSION['group']='';
	$_SESSION['username']='';
	header("Location: index.php?action=login");
}


function run(){
	$id=intval($_REQUEST['id']);
	$limit=intval($_REQUEST['limit']);
	print "<questions id='{$id}'>";
	$q=mysql_query("SELECT a_answer, a_text, a_type, q.q_question, q_text, q_type FROM lab3_question q JOIN lab3_answer ON q.q_question=a_question JOIN (SELECT q_question FROM lab3_test_theme JOIN lab3_question ON q_theme=tt_theme WHERE tt_test={$id} ORDER BY RAND() LIMIT {$limit}) AS t ON t.q_question=q.q_question ORDER BY q.q_question, RAND()");
	sql_split($q,"a_answer","q_question");
	print "</questions>";
}

function check() {
	$id=intval($_REQUEST['id']);
	$val=mysql_real_escape_string($_REQUEST['val']);
	$uid=$_SESSION['user'];
	mysql_query("UPDATE lab3_result SET r_ended_timestamp=CURRENT_TIMESTAMP, r_text='{$val}' WHERE r_test={$id} AND r_user={$uid}");
	print_result($val);
}
function print_result($val){
	$qwes=explode(",",$val);
	$ids=array();
	$pairs=array();
	foreach($qwes as $k => $qwe){
		$q=explode(".",$qwe);
		$ids[]=$q[0];
		$ans[]=$q[2];
		$pairs[]=array_slice($q,3);
	}
	unset($qwes);
	$imp=implode(',',$ids);
	$sql=mysql_query("SELECT * FROM lab3_solution RIGHT JOIN lab3_question ON s_question=q_question WHERE q_question IN ({$imp})");
	//идем по запросу, находим вопрос в массиве, проверяем, удаляем пару из массива пар, если нашли, добавляем, если нет
	while($row=mysql_fetch_assoc($sql)){
		$k=array_search($row['q_question'],$ids);
		switch($row['q_type']){
		case 1:
		case 3:
			if($ans[$k]==$row['q_correct_answer']) $pairs[$k]=0; else $pairs[$k]=explode("_",str_replace("answer_","",$row['q_correct_answer'])); break;
		case 2:
			if(($rem=array_search($row['s_parent']."_0",$pairs[$k]))!==FALSE) unset($pairs[$k][$rem]); else array_push($pairs[$k],'+'.$row['s_parent']);break;
		case 4:
		case 5:
		case 6:
			if(($rem=array_search($row['s_parent']."_".$row['s_child'],$pairs[$k]))!==FALSE) unset($pairs[$k][$rem]); else array_push($pairs[$k],'+'.$row['s_parent']."_".$row['s_child']);break;
		}
	}
	unset($sql);
	$right=0;
	$sql="UPDATE lab3_question SET q_correct_tries = CASE q_question\n ";
	print "<results id='0'>";
	foreach($ids as $k => $id){
		print "<result question='{$id}' ";
		if (empty($pairs[$k])){
			$sql .= "WHEN {$id} THEN q_correct_tries+1\n ";
			print "is_correct='1'/>";
			$right+=1;
		}
		else {
			print "is_correct='0' errors='";
			print_r($pairs[$k]);
			print "'/>";
		}
	}
    print "</results>";
	$sql .="END, q_tries=q_tries+1 WHERE q_question IN ({$imp})";
	mysql_query($sql);
	$total=count($ids);
	$percentage=$total>0?$right/$total:0;
	print "<image percentage='{$percentage}' right='{$right}' total='{$total}'/>";
}
//---------------------------------------------------------
//admin.php
function show_result(){
	$id=intval($_REQUEST['id']);
	$sql=mysql_query("SELECT * FROM lab3_result WHERE r_result={$id}");
	$row=mysql_fetch_assoc($sql);
	print_result($row['r_text']);
}
function test(){
	$id=intval($_REQUEST['id']);
	$uid=$_SESSION['user'];
	$val=mysql_real_escape_string($_REQUEST['val']);
	if($id==-1) {
		mysql_query("INSERT INTO lab3_test(e_test_name,e_added_timestamp,e_added_user) VALUES('{$val}',CURRENT_TIMESTAMP, {$uid})") or print("<error value='".mysql_error()."'/>");
		print "<e_test e_test='".mysql_insert_id()."' e_test_name='{$val}'/>";
	}
	if($id>=0) {
		mysql_query("UPDATE lab3_test SET e_test_name='{$val}' WHERE e_test={$id}");
		print "<e_test e_test='{$id}' e_test_name='{$val}'/>";
	}
}
function test_limit(){
	$id=intval($_REQUEST['id']);
	$val=intval($_REQUEST['val']);
	mysql_query("UPDATE lab3_test SET e_limit={$val} WHERE e_test={$id}");
}
function cat(){
	$id=intval($_REQUEST['id']);
	$uid=$_SESSION['user'];
	$val=mysql_real_escape_string($_REQUEST['val']);
	if($id==-1) {
		mysql_query("INSERT INTO lab3_category(c_category_name,c_added_timestamp,c_added_user) VALUES('{$val}',CURRENT_TIMESTAMP, {$uid})") or print("<error value='".mysql_error()."'/>");
		print "<c_category c_category='".mysql_insert_id()."' c_category_name='{$val}'/>";
	}
	if($id>=0) {
		mysql_query("UPDATE lab3_category SET c_category_name='{$val}' WHERE c_category={$id}");
		print "<c_category c_category='{$id}' c_category_name='{$val}'/>";
	}
}
function theme(){
	$id=intval($_REQUEST['id']);
	$uid=$_SESSION['user'];
	$val=mysql_real_escape_string($_REQUEST['val']);
	$cat=intval($_REQUEST['cat']);
	if($id==-1) {
		mysql_query("INSERT INTO lab3_theme(t_theme_name,t_category,t_added_timestamp,t_added_user) VALUES('{$val}',{$cat},CURRENT_TIMESTAMP, {$uid})") or print("<error value='".mysql_error()."'/>");
		print "<t_theme t_theme='".mysql_insert_id()."' t_theme_name='{$val}'/>";
	}
	if($id>=0) {
		mysql_query("UPDATE lab3_theme SET t_theme_name='{$val}', t_category={$cat} WHERE t_theme={$id}");
		print "<t_theme t_theme='{$id}' t_theme_name='{$val}'/>";
	}
}
function answer(){
	$id=intval($_REQUEST['id']);
	$question=intval($_REQUEST['question']);
	$type=intval($_REQUEST['type']);
	$q_type=intval($_REQUEST['q_type']);
	$val=mysql_real_escape_string($_REQUEST['val']);
	if($id==-1) {
		mysql_query("INSERT INTO lab3_answer(a_text,a_question,a_type) VALUES('{$val}',{$question},{$type})") or print("<error value='".mysql_error()."'/>");
		print "<q_stub q_type='{$q_type}'><a_answer a_answer='".mysql_insert_id()."' a_text='{$val}' a_type='{$type}' q_type='{$q_type}'/></q_stub>";
	}
	if($id>=0) {
		mysql_query("UPDATE lab3_answer SET a_text='{$val}' WHERE a_answer={$id}");
		print "<q_stub q_type='{$q_type}'><a_answer a_answer='{$id}' a_text='{$val}' a_type='{$type}' q_type='{$q_type}'/></q_stub>";
	}
}
function question(){
	$id=intval($_REQUEST['id']);
	$theme=intval($_REQUEST['theme']);
	$val=mysql_real_escape_string($_REQUEST['val']);
	if($id==-1) {
		mysql_query("INSERT INTO lab3_question(q_theme, q_text, q_correct_answer) VALUES ({$theme}, '', '')");
		print "<q_question q_question='".mysql_insert_id()."' q_text=''/>";
	}
	if($id>=0) {
		mysql_query("UPDATE lab3_question SET q_text='{$val}' WHERE q_question={$id}");
	}
}
function tt_set(){
	$id=intval($_REQUEST['id']);
	$theme=intval($_REQUEST['theme']);
	mysql_query("INSERT INTO lab3_test_theme(tt_test,tt_theme) VALUES ({$id},{$theme})");	
}
function tt_del(){
	$id=intval($_REQUEST['id']);
	$theme=intval($_REQUEST['theme']);
	mysql_query("DELETE FROM lab3_test_theme WHERE tt_test={$id} AND tt_theme={$theme}");	
}
function result() {
	$user=intval($_REQUEST['user']);
	$test=intval($_REQUEST['test']);
	mysql_query("INSERT INTO lab3_result (r_user, r_test) VALUES({$user}, {$test});");	
}
function delete(){
	$id=intval($_REQUEST['id']);
	$what=mysql_real_escape_string($_REQUEST['what']);
	switch($what){
	case 'test':
		mysql_query("DELETE FROM lab3_test WHERE e_test={$id}");
		mysql_query("DELETE FROM lab3_test_theme WHERE tt_test={$id}");
		break;
	case 'cat':
		mysql_query("DELETE FROM lab3_category WHERE c_category='{$id}'");
		mysql_query("DELETE FROM lab3_theme WHERE t_category='{$id}'");
		break;
	case 'theme':
		mysql_query("DELETE FROM lab3_theme WHERE t_theme='{$id}'");
		mysql_query("DELETE FROM lab3_test_theme WHERE tt_theme={$id}");
		break;
	case 'ans':
		mysql_query("DELETE FROM lab3_answer WHERE a_answer='{$id}'");
		break;
	case 'qwe':
		mysql_query("DELETE FROM lab3_question WHERE q_question='{$id}'");
		mysql_query("DELETE FROM lab3_answer WHERE a_question='{$id}'");
		break;
	case 'result':
		$user=intval($_REQUEST['user']);
		$test=intval($_REQUEST['test']);
		mysql_query("DELETE FROM lab3_result WHERE r_user={$user} AND r_test={$test}");
		break;
	}
}
function sortorder(){
	$what=mysql_real_escape_string($_REQUEST['what']);
	switch($what){
	case 'test':
		foreach($_REQUEST['test'] as $i=>$id ) mysql_query("UPDATE lab3_test SET e_sortorder={$i} WHERE e_test={$id}");
		break;
	case 'cat':
		foreach($_REQUEST['cat'] as $i=>$id ) mysql_query("UPDATE lab3_category SET c_sortorder={$i} WHERE c_category={$id}");
		break;
	case 'theme':
		foreach($_REQUEST['theme'] as $i=>$id ) mysql_query("UPDATE lab3_theme SET t_sortorder={$i} WHERE t_theme={$id}");
		break;
	case 'ans':
		foreach($_REQUEST['answer'] as $i=>$id ) mysql_query("UPDATE lab3_answer SET a_sortorder={$i} WHERE a_answer={$id}");
		break;
	case 'qwe':
		foreach($_REQUEST['qwe'] as $i=>$id ) mysql_query("UPDATE lab3_question SET q_sortorder={$i} WHERE q_question={$id}");
		break;
	}
}
function modify(){
	$id=intval($_REQUEST['id']);
	print "<questions id='{$id}'>";
	$q=mysql_query("SELECT q_question, q_type, q_text, a_answer, a_text, a_type FROM lab3_answer RIGHT JOIN lab3_question ON a_question=q_question WHERE q_theme={$id} ORDER BY q_question, a_sortorder");
	sql_split($q,"a_answer","q_question");
	print "</questions>";
	print "<solutions id='{$id}'>";
	$q=mysql_query("SELECT * FROM lab3_solution RIGHT JOIN lab3_question ON s_question=q_question WHERE q_theme={$id}");
	sql_split($q,"s_solution","q_question");
	print "</solutions>";
}
function modify_type(){
	$id=intval($_REQUEST['id']);
	$type=intval($_REQUEST['type']);
	$onecol=($type<4);
	mysql_query("UPDATE lab3_question SET q_type={$type} WHERE q_question={$id}");
	$q=mysql_query("SELECT q_question, q_type, q_text, a_answer, a_text, a_type FROM lab3_answer RIGHT JOIN lab3_question ON a_question=q_question WHERE q_question={$id} ORDER BY q_sortorder, a_sortorder");
	sql_split($q,"a_answer","q_question");
	//print "<q_question q_question='{$id}' q_type='{$type}'/>";
}
function modify_correct(){
	$id=intval($_REQUEST['id']);
	$val=mysql_real_escape_string($_REQUEST['val']);
	mysql_query("UPDATE lab3_question SET q_correct_answer='{$val}' WHERE q_question={$id}");
}
function save_solutions(){
	$id=intval($_REQUEST['id']);
	mysql_query("DELETE FROM lab3_solution WHERE s_question IN ( SELECT q_question FROM lab3_question WHERE q_theme={$id} )");
	
	foreach($_REQUEST['s'] as $i=>$s ) {
		list($s_q,$s_p,$s_c)=explode('_',$s);
		mysql_query("INSERT INTO lab3_solution(s_question, s_parent, s_child) VALUES ({$s_q},{$s_p},{$s_c})");
	}
}
function stats(){
	$id=intval($_REQUEST['id']);
	$q=mysql_query("SELECT r_result, r_ended_timestamp, u_user, u_name FROM lab3_result RIGHT JOIN lab3_user ON r_user=u_user AND r_test={$id};");
	print "<resultset id='{$id}'>";
	sql_split($q,"r_result","u_user");
	print "</resultset>";
}
?>