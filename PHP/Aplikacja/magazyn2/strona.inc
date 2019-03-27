<?php
class strona
{
	private $conn;
	public function __construct()
	{
		$this->conn = new mysqli("localhost", "root", "", "magazyn2");
		if ($this->conn->connect_error) die("Connection failed: " . $this->conn->connect_error);
	}
	public function czyIstnieje($login, $haslo){
	
		$sql = "SELECT id, login, haslo FROM pracownik where login='$login'";
		$result = $this->conn->query($sql);

		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			if($row["haslo"]==md5($haslo)){
				//echo "Hasło poprawne";
				return true;
				}else{
					echo "Nie poprawne hasło";
				}
			}
		} else echo "Nie istnieje taki użytkownik";
		//return true;
		return false; // brak użytkownika lub niezgodne hasło
	}
	public function getPozycja($login){
		$sql = "SELECT pozycja FROM pracownik where login='$login'";
		$result = $this->conn->query($sql);
		if($result->num_rows==0) echo "Użytkownik o loginie $login nie istnieje";
		elseif($result->num_rows==1){
			$row = $result->fetch_assoc();
			//echo "Pozycja ".$row["pozycja"]."<br/>";
			return $row["pozycja"];
		}
	}
	public function bStart(){
		echo "
		<html>
			<head>
				<meta charset='utf-8'>
				<title>Magazyn</title>
				<link rel='stylesheet' href='style.css' type='text/css'>
			</head>
		<body bgcolor='#ffff99'>
		"; //<link rel='stylesheet' href='style.css' type='text/css'>
	}
	public function bEnd(){
		echo "</p> </div> </body> </html>
		";
	}
	private function h1($komunikat){
		echo "
		<div id='Header'><h1>$komunikat</h1></div>
		";
	}
	public function content(){
		echo "<div id='Content'><p>";
	}
	public function session(){
		echo "<p align='right'>Zalogowany jako: ".$_SESSION['user']."</p>";
		//echo "<p align='right'>Pozycja: ".$_SESSION['pozycja']."</p>";
	}
	private function form($a,$b){
		echo "
		<form action='control.php' method='post'>
			<input type='submit' value='$a'><br/>
			<input type='hidden' name='nazwa' value='$b'/>
		</form>
		";
	}
	private function formID($a,$b,$c){
		echo "
		<form action='control.php' method='post'>
			<input type='submit' value='$a'><br/>
			<input type='hidden' name='nazwa' value='$b'/>
			<input type='hidden' name='id' value='$c'/>
		</form>
		";
	}
	private function sForm($a){
		echo "<form action='control.php' method='post'> <table width=$a>";
	}
	private function typeForm($a,$b,$c){ //Nazwa,typ,nazwa zmiennej
		echo "
			<tr><td width=25%>$a:</td><td width=75%><input type='$b' name='$c'/></td>
		";
	}
	private function eForm($a,$b){
		echo "</table> 
		<input type='submit' value='$a'/><br/>
		<input type='hidden' name='nazwa' value='$b'/>
		</form>";
	}
	private function eFormID($a,$b,$c){
		echo "</table> 
		<input type='submit' value='$a'/><br/>
		<input type='hidden' name='nazwa' value='$b'/>
		<input type='hidden' name='id' value='$c'/>
		</form>";
	}
	private function eForm2(){
		echo "</table> 
		<input type='submit' value='login'/><br/>
		</form>";
	}
	private function sList($nazwa){
		echo "<select name=$nazwa>";
	}
	private function listForm($a,$b){
		echo "<option value=$a>$b</option>";
	}
	private function eList(){
		echo "</select>";
	}
	private function choose($arg,$lista,$opis){
		echo "<tr><td width=25%>$opis:</td><td width=75%>";
		$this->sList($arg);
		for($i = 0, $cnt = count($lista); $i < $cnt; $i++ ){
			$this->listForm($lista[$i],$lista[$i]);
		}
		$this->eList();
		echo "</td></tr>";
	}
	private function choose2($arg,$lista,$opis){
		echo "<tr><td width=25%>$opis:</td><td width=75%>";
		$this->sList($arg);
		for($i = 0, $cnt = count($lista[0]); $i < $cnt; $i++ ){
			$this->listForm($lista[0][$i],$lista[1][$i]);
		}
		$this->eList();
		echo "</td></tr>";
	}
	private function czyChcesz($a){
		echo "<br><center>Czy chcesz pozostać w danej funkcji?
		<table><tr><td><form action='control.php' method='post'>
			<input type='submit' value='TAK'><br/>
			<input type='hidden' name='nazwa'value='$a'/>
		</form></td>
		<td><form action='control.php' method='post'>
			<input type='submit' value='NIE'><br/>
		</form></td>
		</tr></table></center>";
	}
	private function przerwij(){
		echo "<p><a href='control.php'>Powrót</a></p></div>";
	}
	public function displayLogin(){
		$this->h1("Logowanie do systemu");
		$this->content();
		$this->sForm(250);
		$this->typeForm('Login','text','login');
		$this->typeForm('Hasło','password','haslo');
		$this->eForm2();
	}
	function displayMenuAdmin(){
		$this->session();
		$this->h1("Magazyn");
		$this->content();
		$this->form("Zarządzaj użytkownikami","manageUsers");
		$this->form("Zarządzaj przedmiotami","manageItems");
		$this->form("Zarządzaj lokalizacjami","manageLocations");
		$this->form("Wyloguj się","quit");
	}
	
	//TU ZACZYNA SIE ZARZADZAJ UŻYTKOWNIKAMI
	
	function manageUsers(){
		$this->session();
		$this->h1("Zarządzaj użytkownikami");
		$this->content();

		echo "<h2>Wszyscy użytkownicy</h2>";

		$sql = "SELECT id,login,pozycja FROM v_pracownicy";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>Login</td><td>Pozycja</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["login"]. " </td><td> " . $row["pozycja"] ."</td><td>";
			$this->formID("wyświetl","displayUser",$row["id"]);
			echo "</td><td>";
			$this->formID("zmien","updateUser",$row["id"]);
			echo "</td><td>";
			$this->formID("usun","removeUser",$row["id"]);
			echo "</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";
		
		echo "<h2>Dodaj uzytkownika</h2>";
		
		$this->sForm(300);
		$this->typeForm('Login','text','login');
		$this->typeForm('Haslo','password','haslo');
		
		$sql = "SELECT id,nazwa FROM pozycja";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista[0][$i]=$row["id"];
			$lista[1][$i]=$row["nazwa"];
			$i++;
			//echo $row["id"]." ". $row["nazwa"];
			}
		} else echo "0 results";

		$this->choose2('pozycja',$lista,'Pozycja');
		$this->eForm('Dodaj uzytkownika','insertUser');
		
		$this->czyChcesz("manageUsers");
		$this->przerwij();
	}
	function insertUser(){
		$this->session();
		$this->h1("Dodanie użytkownika");
		$this->content();

		$a = array($_POST['login'],$_POST['haslo'],$_POST['pozycja']);
		
		$sql = "INSERT INTO pracownik (login, haslo, pozycja)
		VALUES ('$a[0]', md5('$a[1]'), '$a[2]');";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageUsers");
		$this->przerwij();
	}
	function displayUser(){
		$this->session();
		$this->h1("Wyświetl dane użytkownika");
		$this->content();
		$id = $_POST['id'];
		
		$sql = "SELECT id,login,pozycja FROM v_pracownicy where id=$id";
		$result = $this->conn->query($sql);
		if($result->num_rows==0) echo "Użytkownik o id $id nie istnieje";
		else if ($result->num_rows > 0) {
			echo "<div><table><tr><td>ID</td><td>Login</td><td>Pozycja</td></tr>";
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["login"]. " </td><td> " . $row["pozycja"]."</td></tr>";
			}
		}
		echo "</table>";

		$this->czyChcesz("manageUsers");
		$this->przerwij();
	}
	function updateUser(){
		$this->session();
		$this->h1("Zmień dane użytkownika");
		$this->content();
		$this->sForm(500);
		$id = $_POST['id'];
		$this->typeForm('Nowe Haslo','password','haslo');
		
		$sql = "SELECT id,nazwa FROM pozycja";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista2[0][$i]=$row["id"];
			$lista2[1][$i]=$row["nazwa"];
			$i++;
			}
		} else echo "0 results";
		$this->choose2('pozycja',$lista2,'Nowa pozycja');

		$this->eFormID('OK','replaceUser',$id);
		$this->przerwij();
	}
	function replaceUser(){
		$this->session();
		$this->h1("Zaktualizuj dane");
		$this->content();
		$id = $_POST['id'];
		$a = array($_POST['haslo'],$_POST['pozycja']);
		
		$sql = "UPDATE pracownik
				SET haslo = md5('$a[0]'), pozycja = '$a[1]'
				WHERE id = $id;";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageUsers");
		$this->przerwij();
	}
	function removeUser(){
		$this->session();
		$this->h1("Usuń dane");
		$this->content();

		$id = $_POST['id'];

		$sql = "SELECT id, login, pozycja FROM pracownik where id=$id";
		$result = $this->conn->query($sql);
		if($result->num_rows==0) echo "Użytkownik o $id $nr nie istnieje";
		else if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "Id: " . $row["id"]. " Login: " . $row["login"]. " Pozycja: " . $row["pozycja"]."<br>";
			}
			$sql = "DELETE FROM pracownik where id=$id;";
			$this->conn->query($sql);
			echo "Użytkownik usunięty";
		}
		$this->czyChcesz("manageUsers");
		$this->przerwij();
	}
	
	//TU ZACZYNA SIE ZARZADZAJ PRZEDMIOTAMI
	
	function manageItems(){
		$this->session();
		$this->h1("Zarządzaj przedmiotami");
		$this->content();

		echo "<h2>Wszystkie przedmioty</h2>";
		
		$sql = "SELECT id,nazwa,adres,kategoria FROM v_przedmioty";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>Przedmiot</td><td>Adres</td><td>Kategoria</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["nazwa"]. " </td><td> " 
			. $row["adres"] ."</td><td> " . $row["kategoria"] ."</td><td>";
			$this->formID("wyświetl","displayItem",$row["id"]);
			echo "</td><td>";
			$this->formID("zmien","updateItem",$row["id"]);
			echo "</td><td>";
			$this->formID("usun","removeItem",$row["id"]);
			echo "</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";
		
		echo "<h2>Dodaj przedmiot</h2>";
		
		$this->sForm(300);
		$this->typeForm('Nazwa','text','przedmiot');
		$this->typeForm('Opis','text','opis');

		$sql = "SELECT id,adres FROM lokalizacja";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista[0][$i]=$row["id"];
			$lista[1][$i]=$row["adres"];
			$i++;
			}
		} else echo "0 results";
		
		$sql = "SELECT id,nazwa FROM kategorie";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista2[0][$i]=$row["id"];
			$lista2[1][$i]=$row["nazwa"];
			$i++;
			}
		} else echo "0 results";
		
		$this->choose2('lokalizacja',$lista,'Lokalizacja');
		$this->choose2('kategoria',$lista2,'Kategoria');
		
		$this->eForm('OK','insertItem');

		$this->czyChcesz("manageItems");
		$this->przerwij();
	}
	function insertItem(){
		$this->session();
		$this->h1("Dodanie przedmiotu");
		$this->content();

		$a = array($_POST['przedmiot'],$_POST['opis'],$_POST['lokalizacja'],$_POST['kategoria']);
		
		$sql = "INSERT INTO przedmiot (nazwa, opis, lokalizacja, kategoria)
		VALUES ('$a[0]', '$a[1]', '$a[2]', '$a[3]');";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageItems");
		$this->przerwij();
	}
	function displayItem(){
		$this->session();
		$this->h1("Wyświetl dane przedmiotu");
		$this->content();
		$id = $_POST['id'];
		
		$sql = "SELECT id,nazwa,opis,adres,kategoria FROM v_przedmioty where id=$id";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>Przedmiot</td><td>Opis</td><td>Adres</td><td>Kategoria</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["nazwa"]. " </td><td> ". $row["opis"]. " </td><td> "
			. $row["adres"] ."</td><td> " . $row["kategoria"] ."</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		$this->czyChcesz("manageItems");
		$this->przerwij();
	}
	function updateItem(){
		$this->session();
		$this->h1("Zmień dane przedmiotu");
		$this->content();
		$this->sForm(500);
		$this->typeForm('Nowa nazwa','text','przedmiot');
		$this->typeForm('Nowy opis','text','opis');

		$id = $_POST['id'];

		$sql = "SELECT id,adres FROM lokalizacja";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista[0][$i]=$row["id"];
			$lista[1][$i]=$row["adres"];
			$i++;
			}
		} else echo "0 results";
		
		$sql = "SELECT id,nazwa FROM kategorie";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista2[0][$i]=$row["id"];
			$lista2[1][$i]=$row["nazwa"];
			$i++;
			}
		} else echo "0 results";
		
		$this->choose2('lokalizacja',$lista,'Nowa lokalizacja');
		$this->choose2('kategoria',$lista2,'Nowa kategoria');
		
		$this->eFormID('OK','replaceItem',$id);
		$this->przerwij();
	}
	function replaceItem(){
		$this->session();
		$this->h1("Zaktualizuj dane przedmiotu");
		$this->content();
		$id = $_POST['id'];
		$a = array($_POST['przedmiot'],$_POST['opis'],$_POST['lokalizacja'],$_POST['kategoria']);
		
		$sql = "UPDATE przedmiot
				SET nazwa = '$a[0]', opis = '$a[1]', lokalizacja = '$a[2]', kategoria = '$a[3]'
				WHERE id = $id;";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageItems");
		$this->przerwij();
	}
	function removeItem(){
		$this->session();
		$this->h1("Usuń przedmiot");
		$this->content();

		$id = $_POST['id'];
		
		$sql = "SELECT id from przedmiot where id=$id";
		
		$result = $this->conn->query($sql);
		if($result->num_rows==0) echo "Przedmiot o id $id nie istnieje";
		else if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "Id: " . $row["id"]. "<br>";
			}
			$sql = "Delete FROM przedmiot where id=$id";
			$this->conn->query($sql);
			echo "Przedmiot usunięty";
		}
		$this->czyChcesz("manageItems");
		$this->przerwij();
	}
	
	//TU ZACZYNA SIE ZARZADZAJ LOKALIZACJAMI
	
	function manageLocations(){
		$this->session();
		$this->h1("Zarządzaj lokalizacjami");
		$this->content();

		echo "<h2>Wszystkie lokalizacje</h2>";

		$sql = "SELECT id,adres FROM lokalizacja";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>adres</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["adres"]. " </td><td>";
			$this->formID("wyświetl","displayLoc",$row["id"]);
			echo "</td><td>";
			$this->formID("zmien","updateLoc",$row["id"]);
			echo "</td><td>";
			$this->formID("usun","removeLoc",$row["id"]);
			echo "</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		echo "<h2>Dodaj lokalizacje</h2>";

		$this->sForm(500);
		$this->typeForm('Adres','text','adres');
		
		$this->eForm('OK','insertLoc');

		$this->czyChcesz("manageLocations");
		$this->przerwij();
	}
	function insertLoc(){
		$this->session();
		$this->h1("Dodanie lokalizacji");
		$this->content();

		$a = array($_POST['adres']);
		
		$sql = "INSERT INTO lokalizacja (adres)
		VALUES ('$a[0]');";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageLocations");
		$this->przerwij();
	}
	function displayLoc(){
		$this->session();
		$this->h1("Wyświetl dane przedmiotu");
		$this->content();
		$id = $_POST['id'];
		
		$sql = "SELECT id,adres FROM lokalizacja where id=$id";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>adres</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["adres"]. " </td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		$this->czyChcesz("manageLocations");
		$this->przerwij();
	}
	function updateLoc(){
		$this->session();
		$this->h1("Zmień dane lokalizacji");
		$this->content();
		$id = $_POST['id'];

		$this->sForm(500);
		$this->typeForm('Adres','text','adres');
		
		$this->eFormID('OK','replaceLoc',$id);
		$this->przerwij();
	}
	function replaceLoc(){
		$this->session();
		$this->h1("Zaktualizuj dane lokalizacji");
		$this->content();
		$id = $_POST['id'];
		
		$a = array($_POST['adres']);
		
		$sql = "UPDATE lokalizacja
				SET adres = '$a[0]'
				WHERE id = $id;";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("manageLocations");
		$this->przerwij();
	}
	function removeLoc(){
		$this->session();
		$this->h1("Usuń lokalizację");
		$this->content();

		$id = $_POST['id'];
		
		$sql = "SELECT id from lokalizacja where id=$id";
		
		$result = $this->conn->query($sql);
		if($result->num_rows==0) echo "Lokalizacja o id $id nie istnieje";
		else if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "Id: " . $row["id"]. "<br>";
			}
			$sql = "Delete FROM lokalizacja where id=$id";
			$this->conn->query($sql);
			echo "Lokalizacja usunięta";
		}
		$this->czyChcesz("manageLocations");
		$this->przerwij();
	}
	
	// Aktor: Pracownik
	
	function displayMenuPracownik(){
		$this->session();
		$this->h1("Program do obsługi systemu");
		$this->content();
		$this->form("Pobierz zadanie","getTask");
		$this->form("Wyloguj się","quit");
	}
	
	function getTask($user){
		$this->session();
		$this->h1("Pobierz zadanie");

		$this->content();
		
		echo "<h2>Wszystkie zadania</h2>";

		$sql = "SELECT id, przedmiot, przydzielony_harmonogram, stan, przydzielony_pracownikowi 
		FROM v_zadania where przydzielony_pracownikowi='$user' and stan_id=2";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td> <td>Przedmiot</td> <td>Przydzielony harmonogram</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. "  </td><td> "
			. $row["przedmiot"] ."</td><td> ". $row["przydzielony_harmonogram"]
			."</td><td>";
			$this->formID("wykonaj zadanie","showItemLocation",$row["id"]);
			echo "</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		$this->przerwij();
	}
	
	function showItemLocation(){
		$this->session();
		$this->h1("Lokalizacja przedmiotu");
		$this->content();
		$id = $_POST['id'];

		$sql = "SELECT id,stworzony_przez, przydzielony_pracownikowi, przedmiot,
		adres_przedmiotu, lokalizacja_zadania, stan, utworzony, przydzielony_harmonogram FROM v_zadania where id=$id";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>stworzony przez</td><td>Przedmiot</td><td>Adres przedmiotu</td>
		<td>Lokalizacja zadania</td><td>Utworzony</td><td>Przydzielony harmonogram</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["stworzony_przez"]. " </td><td> " 
			. $row["przedmiot"] ."</td><td> ". $row["adres_przedmiotu"]."</td><td> ". $row["lokalizacja_zadania"]."</td><td> "
			. $row["utworzony"]."</td><td> ". $row["przydzielony_harmonogram"]
			."</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";
		echo "<h2>Zatwierdz kiedy wykonasz zadanie</h2>";
		$this->formID("Zadanie wykonane","replaceItemLocation",$id);
		$this->czyChcesz("getTask");

		$this->przerwij();
	}
	function replaceItemLocation(){
		$this->session();
		$this->h1("Ustaw lokalizacje przedmiotu");
		$this->content();
		$id = $_POST['id'];

		$sql = "SELECT id_przedmiotu, lokalizacja_zadania_id FROM v_zadania where id=$id";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			$loc_id = $row["lokalizacja_zadania_id"];
			$item_id = $row["id_przedmiotu"];
			}
		} else echo "0 results";

		$sql = "UPDATE przedmiot
				SET lokalizacja = $loc_id
				WHERE id = $item_id;";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$sql = "UPDATE zadanie
				SET stan = 3
				WHERE id = $id;";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;

		$this->czyChcesz("getTask");
		$this->przerwij();
	}

	// Aktor: Kierownik
	
	function displayMenuKierownik(){
		$this->session();
		$this->h1("Program do obsługi systemu");
		$this->content();

		echo "<h2>Wszystkie zadania</h2>";

		$sql = "SELECT id,stworzony_przez, przydzielony_pracownikowi, przedmiot,
		adres_przedmiotu, lokalizacja_zadania, stan, utworzony, przydzielony_harmonogram FROM v_zadania";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>Przydzielony pracownik</td>
		<td>Przedmiot</td><td>Adres przedmiotu</td><td>Lokalizacja zadania</td>
		<td>stan</td><td>Utworzony</td><td>Przydzielony harmonogram</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. "  </td><td> "
			. $row["przydzielony_pracownikowi"] ."</td><td> " . $row["przedmiot"] ."</td><td> " 
			. $row["adres_przedmiotu"]."</td><td> ". $row["lokalizacja_zadania"]."</td><td> "
			. $row["stan"]."</td><td> ". $row["utworzony"]."</td><td> ". $row["przydzielony_harmonogram"]
			."</td><td>";
			$this->formID("wyświetl","displayTask",$row["id"]);
			echo "</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		echo "<h2>Dodaj zadanie</h2>";

		$this->sForm(500);

		$sql = "SELECT id,login,pozycja FROM pracownik";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			if($row["pozycja"]==2) {//jesli pracownik
				$lista[0][$i]=$row["id"];
				$lista[1][$i]=$row["login"];
				$i++;
				}
			}
		} else echo "0 results";
		$this->choose2('pracownik',$lista,'Wybierz pracownika');

		$sql = "SELECT id,nazwa FROM przedmiot";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista2[0][$i]=$row["id"];
			$lista2[1][$i]=$row["nazwa"];
			$i++;
			}
		} else echo "0 results";
		$this->choose2('przedmiot',$lista2,'Wybierz Przedmiot');

		$sql = "SELECT id,adres FROM lokalizacja";
		$result = $this->conn->query($sql);
		
		if ($result->num_rows > 0) {
			$i=0;
			while($row = $result->fetch_assoc()) {
			$lista3[0][$i]=$row["id"];
			$lista3[1][$i]=$row["adres"];
			$i++;
			}
		} else echo "0 results";
		$this->choose2('loc_id',$lista3,'Wybierz lokalizację');
		$this->typeForm('Przydziel harmonogram','date','przydzielony_harmonogram');
		
		$this->eForm('OK','insertTask');
		$this->form("Wyloguj się","quit");
	}
	function insertTask($user){
		$this->session();
		$this->h1("Dodaj zadanie");
		$this->content();
		
		$sql2 = "SELECT id FROM pracownik where login='$user'";
		$result2 = $this->conn->query($sql2);
		if($result2->num_rows==0) echo "Użytkownik $user nie istnieje";
		elseif($result2->num_rows == 1){
			$row = $result2->fetch_assoc();
			//echo $user." ".$row["id"];
			$user_id=$row["id"];
		}
		$a = array($user_id,$_POST['pracownik'],$_POST['przedmiot'],$_POST['loc_id'],date("Y-m-d"),
		$_POST['przydzielony_harmonogram'],2);
		
		$sql = "INSERT INTO zadanie (stworzony_przez, przydzielony_pracownikowi, przedmiot, lokalizacja_zadania, utworzony, przydzielony_harmonogram, stan)
		VALUES ('$a[0]', '$a[1]', '$a[2]', '$a[3]', '$a[4]', '$a[5]', '$a[6]');";

		if ($this->conn->query($sql) === TRUE) {
			echo "OK - dane wprowadzono<br/>";
		} else echo "Błąd: " . $sql . "<br>" . $this->conn->error;
		$this->przerwij();
	}
	function displayTask(){
		$this->session();
		$this->h1("Wyświetl zadanie");
		$this->content();
		$id = $_POST['id'];
		
		$sql = "SELECT id,stworzony_przez, przydzielony_pracownikowi, przedmiot,
		adres_przedmiotu, lokalizacja_zadania, stan, utworzony, przydzielony_harmonogram FROM v_zadania where id=$id";
		$result = $this->conn->query($sql);
		
		echo "<table><tr><td>ID</td><td>stworzony przez</td><td>Przydzielony pracownikowi</td>
		<td>Przedmiot</td><td>Adres przedmiotu</td><td>Lokalizacja zadania</td>
		<td>stan</td><td>Utworzony</td><td>Przydzielony harmonogram</td></tr>";
		if ($result->num_rows > 0) {
			while($row = $result->fetch_assoc()) {
			echo "<tr><td>" . $row["id"]. ". </td><td> " . $row["stworzony_przez"]. " </td><td> " 
			. $row["przydzielony_pracownikowi"] ."</td><td> " . $row["przedmiot"] ."</td><td> " 
			. $row["adres_przedmiotu"]."</td><td> ". $row["lokalizacja_zadania"]."</td><td> "
			. $row["stan"]."</td><td> ". $row["utworzony"]."</td><td> ". $row["przydzielony_harmonogram"]
			."</td></tr>";
			}
		} else echo "0 results";
		echo "</table>";

		$this->przerwij();
	}
	public function __destruct(){
		$this->conn->close();
	}
}
?>
