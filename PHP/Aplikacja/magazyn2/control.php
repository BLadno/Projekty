<?php
	require_once('strona.inc');
	
	$ptr=new strona();
	$ptr->bStart();
	
	session_start();
	
	if (!isset($_SESSION['init']))
	{
		session_regenerate_id();
		$_SESSION['init'] = true; 
	}
	
if(empty($_SESSION['user'])){
   if(!empty($_POST['login'])and !empty($_POST['haslo']))
	{                                                     
		if ($ptr->czyIstnieje($_POST['login'],$_POST['haslo']))
		{                                                      
			$_SESSION['user']=$_POST['login'];
			$_SESSION['pozycja']=$ptr->getPozycja($_POST['login']);
			unset($_POST['haslo']);
			unset($_POST['login']);
			if($_SESSION['pozycja']==1) $ptr->displayMenuAdmin();
			elseif($_SESSION['pozycja']==2) $ptr->displayMenuPracownik();
			elseif($_SESSION['pozycja']==3) $ptr->displayMenuKierownik();
			else echo "Nieznana pozycja";
		}else{
			$ptr->displayLogin();
		}
    }else{
		$ptr->displayLogin();		
    }
	
}else{
	if (isset($_POST['nazwa'])){$akcja=$_POST['nazwa'];
	}else{
		if($_SESSION['pozycja']==1) $ptr->displayMenuAdmin();
		elseif($_SESSION['pozycja']==2) $ptr->displayMenuPracownik();
		elseif($_SESSION['pozycja']==3) $ptr->displayMenuKierownik();
		else echo "Nieznana pozycja";
		exit;
	}
	if($_SESSION['pozycja']==1){
		if($akcja=='manageUsers') $ptr->manageUsers();
		elseif($akcja=='manageItems') $ptr->manageItems();
		elseif($akcja=='manageLocations') $ptr->manageLocations();
		
		elseif($akcja=='showUsers') $ptr->showUsers();
		elseif($akcja=='insertUser') $ptr->insertUser();
		elseif($akcja=='displayUser') $ptr->displayUser();
		elseif($akcja=='updateUser') $ptr->updateUser();
		elseif($akcja=='replaceUser') $ptr->replaceUser();
		elseif($akcja=='removeUser') $ptr->removeUser();
		
		elseif($akcja=='showItems') $ptr->showItems();
		elseif($akcja=='insertItem') $ptr->insertItem();
		elseif($akcja=='displayItem') $ptr->displayItem();
		elseif($akcja=='updateItem') $ptr->updateItem();
		elseif($akcja=='replaceItem') $ptr->replaceItem();
		elseif($akcja=='removeItem') $ptr->removeItem();
		
		elseif($akcja=='showLocs') $ptr->showLocs();
		elseif($akcja=='insertLoc') $ptr->insertLoc();
		elseif($akcja=='displayLoc') $ptr->displayLoc();
		elseif($akcja=='updateLoc') $ptr->updateLoc();
		elseif($akcja=='replaceLoc') $ptr->replaceLoc();
		elseif($akcja=='removeLoc') $ptr->removeLoc();
		//else echo "nieznana akcja ".$akcja ;exit;
	}elseif($_SESSION['pozycja']==2){
		
		if($akcja=='getTask') $ptr->getTask($_SESSION['user']);
		elseif($akcja=='showItemLocation') $ptr->showItemLocation();
		elseif($akcja=='replaceItemLocation') $ptr->replaceItemLocation();
		
	}elseif($_SESSION['pozycja']==3){
		
		if($akcja=='showTasks') $ptr->showTasks();
		elseif($akcja=='displayTask') $ptr->displayTask();
		elseif($akcja=='insertTask') $ptr->insertTask($_SESSION['user']);
		
	}else{
		echo "nieznana pozycja ".$akcja ;exit;
	}
	if ($akcja=='quit'){
		session_destroy();
		session_unset();
		$ptr->DisplayLogin();
	}
}
$ptr->bEnd();
?>
