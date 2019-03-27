<html>
<body bgcolor='#ffff99'>
<?php
	require_once('strona.inc');
	session_start();
	
	if (!isset($_SESSION['init']))
	{
		session_regenerate_id();
		$_SESSION['init'] = true;
		
	}
	
	$ptr=new strona();
	
if(empty($_SESSION['user'])){
   if(!empty($_POST['login'])and !empty($_POST['haslo'])){
		if ($ptr->czyIstnieje($_POST['login'],$_POST['haslo'])){ 
			$_SESSION['user']=$_POST['login']; 
			unset($_POST['haslo']);            
			unset($_POST['login']);
			$ptr->displayMenu();   
			
		}else{
			$ptr->displayLogin();
			
		}
    }else{
		$ptr->displayLogin();		
		
    }
	
}else{
	
	if (isset($_POST['nazwa'])){$akcja=$_POST['nazwa'];
	}else{
		$ptr->displayMenu();
		exit;
		
	}
	if ($akcja=='input'){
		$ptr->displayForm();
		
	}elseif($akcja=='display'){	
		$ptr->displayData();
		
	}elseif ($akcja=='insert'){
		
		if($_POST['imie']!="" and $_POST['nazwisko']!=""and $_POST['pesel']!=""and$_POST['kod']!="" and $_POST['miasto']!="" and $_POST['adres']!=""){
			$ptr->insertData();
		}else{
			echo "Brakujące dane<br/>";
			$ptr->displayForm();
		}
		
	}elseif ($akcja=='addUser'){
		$ptr->addUser();
		
	}elseif ($akcja=='insert2'){
		
		if($_POST['login']!="" and $_POST['haslo']!=""){
			$ptr->insertUser();
			
		}else{
			echo "Brakujące dane<br/>";
			$ptr->addUser();
		}
		
	}elseif ($akcja=='addEvent'){
		$ptr->addEvent();
	}elseif ($akcja=='insert3')	{
		if($_POST['imie']!="" and $_POST['nazwisko']!=""and $_POST['event']!=""and $_POST['price']!=""){
			$ptr -> loadClients();
			
			if($ptr -> czyIstniejeKlient($_POST['imie'],$_POST['nazwisko'])){
				$ptr->insertEvent();
			}else{
				echo "Nie istnieje taki uzytkownik w bazie danych<br/>";
				$ptr->addEvent();
			}
			
		}else{
			echo "Brakujące dane<br/>";
			$ptr->addEvent();
		}
		
	}elseif($akcja=='displayEvent'){							
		$ptr->displayEvent();	
	}elseif ($akcja=='quit'){
		session_destroy();
		session_unset(); 
		$ptr->DisplayLogin();
	}else{
		echo "błąd operacji";exit;
	}
}
?>
</body>
</html>