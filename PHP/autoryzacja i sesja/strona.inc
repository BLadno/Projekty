<?php
class strona
{
	private $users=array();
	
	public function __construct(){
		if(!file_exists("users.csv")){
			$this->users[0]=array('login'=>'admin','haslo'=>md5('admin'));
		}else{
			$row = 0;
			$handle = fopen("users.csv", "r");
			while (($data = fgetcsv($handle, 1000, ";")) == TRUE) {
				$this->users[$row]=array('login'=>$data[0],'haslo'=>md5($data[1]));
				$row++;
			}
			fclose($handle);
		}
	}

	public function czyIstnieje($login, $haslo){
		for($i=0;$i<count($this->users);$i++){
			if($this->users[$i]['login'] == $login and $this->users[$i]['haslo'] == md5($haslo)){
				return true;
			}
		}
		return false;
	}
	
	public function displayLogin(){
	if(!file_exists("users.csv")){
		echo "Nie istnieje żadne konto, domyslny login i haslo: admin";
	}
	?>	
		<h3>Logowanie do systemu obsługi pacjentów</h3>
		<form action='control.php' method='post'>
			<table width=250px>
			<tr><td width=25%>Login:</td><td width=75%><input type='text' name='login' style='width:100;font-size:15px'/></td>
			<tr><td>Hasło:</td><td><input type='password' name='haslo' style='width:100;font-size:15px'/></td>
			</table>
			<input type='submit' value='login'/><br/>
		</form>
		</body>
	<?php
	}
	
	function displayMenu(){
	echo "Zalogowany jako: ".$_SESSION['user'];
	?>
		<table width=300px>
		<h2>Program do obsługi pacjenta</h2>
		<tr><form action='control.php' method='post'>
			<td><a>Wprowadź dane pacjenta</a></td>
			<td><input type='submit' value='OK'><br/></td>
			<input type='hidden' name='nazwa'value='input'/>
		</form></tr>
		<tr><form action='control.php' method='post'>
			<td><a>Wyświetl dane pacjentów</a></td>
			<td><input type='submit' value='OK'><br/></td>
			<input type='hidden' name='nazwa'value='display'/>
		</form></tr>
		<tr><form action='control.php' method='post'>
			<td><a>Wystaw rachunek</a></td>
			<td><input type='submit' value='OK'><br/></td>
			<input type='hidden' name='nazwa'value='addEvent'/>
		</form></tr>
		<tr><form action='control.php' method='post'>
			<td><a>Wyświetl historię transakcji</a></td>
			<td><input type='submit' value='OK'><br/></td>
			<input type='hidden' name='nazwa'value='displayEvent'/>
		</form></tr>
		<tr><form action='control.php' method='post'>
			<td><a>Dodaj konto</a></td>
			<td><input type='submit' value='OK'><br/></td>
			<input type='hidden' name='nazwa'value='addUser'/>
		</form></tr>
		</table><br/>
		<form action='control.php' method='post'>
			<input type='submit' value='Wyloguj się'><br/>
			<input type='hidden' name='nazwa'value='quit'/>
		</form>
	<?php
	}

	function displayForm(){
	echo "Zalogowany jako: ".$_SESSION['user'];
	?>
		<h2>Wprowadź dane pacjenta </h2>
			<table width=300px>
				<form action='control.php' method='post'>
				<tr> <td width=33%>Imie*:</td><td width=66%><input type='text' name='imie'><br/></td> </tr>
				<tr> <td>Nazwisko*:</td><td><input type='text' name='nazwisko'><br/></td> </tr>
				<tr> <td>PESEL*:</td><td><input type='text' name='pesel'><br/></td> </tr>
				<tr> <td>Kod*:</td><td><input type='text' name='kod'><br/></td> </tr>
				<tr> <td>Miasto*:</td><td><input type='text' name='miasto'><br/></td> </tr>
				<tr> <td>Adres*:</td><td><input type='text' name='adres'><br/></td> </tr>
				<tr> <td>Telefon:</td><td><input type='text' name='tel'><br/></td> </tr>
				<tr> <td>E-mail:</td><td><input type='text' name='mail'><br/></td> </tr>
			</table>
				<p>* - Pola wymagające wypelnienia.</p>
				<input type='submit' value='OK'><br/>
				<input type='hidden' name='nazwa'value='insert'/>
			</form>
			</tr>
			<br/>
			<a href='control.php'>Powrót</a>
	<?php	
	}
	
	function displayData(){
		echo "<body bgcolor='#ffff99'>";
		echo "Zalogowany jako: ".$_SESSION['user'];
		
		if(!file_exists("clients.csv")){
			echo "<br/><br/>Nie istnieje plik z danymi.<br/>";
		}else{
			echo "<h2> Dane pacjentów</h2>";
			echo "<table width=800px>";
			echo "<tr><td>Imie</td><td>Nazwisko</td><td>PESEL</td><td>Kod</td><td>Miasto</td><td>Adres zamieszkania</td><td>Telefon</td><td>E-mail</td></tr>";
			$handle = fopen("clients.csv", "r");
			while (($data = fgetcsv($handle, 1000, ";")) == TRUE) {
				$num = count($data);
				echo "<tr>";
				for ($i=0; $i < $num; $i++) {echo "<td>$data[$i]</td>";}
				echo "</tr>";
			}
			echo "</table><br/>"; 
			fclose($handle);
		}
		echo "<br/><a href='control.php'>Powrót do menu</a>";
		echo "</body>";	
	}
	
	function insertData(){
		echo "<body bgcolor='#ffff99'>";
		echo "Zalogowany jako: ".$_SESSION['user']."<br/><br/>";
		$klient[0]=$_POST['imie'];
		$klient[1]=$_POST['nazwisko'];
		$klient[2]=$_POST['pesel'];
		$klient[3]=$_POST['kod'];
		$klient[4]=$_POST['miasto'];
		$klient[5]=$_POST['adres'];
		$klient[6]=$_POST['tel'];
		$klient[7]=$_POST['mail'];
		$fp = fopen('clients.csv', 'a');
		fputcsv($fp, $klient,';');
		echo "OK - dane wprowadzono<br/>";
		fclose($fp);
		echo "<a href='control.php'>Powrót do menu</a>";
		echo "</body>";
	}
	
	function addUser(){
	echo "Zalogowany jako: ".$_SESSION['user'];
	?>
	<h2>Wprowadź dane uzytkownika </h2>
		<table width=300px>
			<form action='control.php' method='post'>
			<tr> <td width=33%>Login*:</td><td width=66%><input type='text' name='login'><br/></td> </tr>
			<tr> <td>Hasło*:</td><td><input type='text' name='haslo'><br/></td> </tr>
		</table>
			<input type='submit' value='OK'><br/>
			<input type='hidden' name='nazwa'value='insert2'/>
		</form>
		<p>* - Pola wymagające wypelnienia.</p>
		<br/>
		<a href='control.php'>Powrót</a>
	<?php	
	}
	
	function insertUser(){
		echo "Zalogowany jako: ".$_SESSION['user']."<br/><br/>";
		$user[0]=$_POST['login'];
		$user[1]=$_POST['haslo'];
		$fp = fopen('users.csv', 'a');
		fputcsv($fp, $user,';');
		echo "OK - dodano uzytkownika<br/>";
		fclose($fp);
		echo "<a href='control.php'>Powrót do menu</a>";
	}
	
	function addEvent(){
	echo "Zalogowany jako: ".$_SESSION['user'];
	?>
	<h2>Wprowadż rachunek</h2>
		<table width=300px>
			<form action='control.php' method='post'>
			<tr> <td width=33%>Imie*:</td><td width=66%><input type='text' name='imie'><br/></td> </tr>
			<tr> <td>Nazwisko*:</td><td><input type='text' name='nazwisko'><br/></td> </tr>
			<tr> <td width=33%>Usługa*:</td><td width=66%><input type='text' name='event'><br/></td> </tr>
			<tr> <td width=33%>Cena*:</td><td width=66%><input type='text' name='price'><br/></td> </tr>
		</table>
			<input type='submit' value='OK'><br/>
			<input type='hidden' name='nazwa'value='insert3'/>
		</form>
		<p>* - Pola wymagające wypelnienia.</p>
		<br/>
		<a href='control.php'>Powrót</a>
	<?php	
	}
	
	function insertEvent(){
		echo "<body bgcolor='#ffff99'>";
		echo "Zalogowany jako: ".$_SESSION['user']."<br/><br/>";
		$event[0]=$_POST['imie'];
		$event[1]=$_POST['nazwisko'];
		$event[2]=$_POST['event'];
		$event[3]=$_POST['price'];
		$event[4]=date('d-m-Y H:i:s');
		$event[5]=$_SESSION['user'];
		$fp = fopen('events.csv', 'a');
		fputcsv($fp, $event,';');
		echo "OK - dodano rachunek<br/>";
		fclose($fp);
		echo "<a href='control.php'>Powrót do menu</a>";
		echo "</body>";
	}
	
	function displayEvent(){
		echo "Zalogowany jako: ".$_SESSION['user'];
		
		if(!file_exists("events.csv")){
			echo "<br/><br/>Nie istnieje plik z danymi.<br/>";
		}else{
		
			echo "<h2> Historia transakcji:</h2>";
			echo "<table width=800px>";
			echo "<tr><td>Imie</td><td>Nazwisko</td><td>Usługa</td><td>Cena</td><td>Wystawiono dnia</td><td>Wystawione prez</td></tr>";
			$handle = fopen("events.csv", "r");
			while (($data = fgetcsv($handle, 1000, ";")) == TRUE) {
				$num = count($data);
				echo "<tr>";
				for ($i=0; $i < $num; $i++) {
					if($i==3) echo "<td>$data[$i] zł</td>"; else echo "<td>$data[$i]</td>";
				}
				echo "</tr>";
			}
			echo "</table><br/>"; 
			fclose($handle);
		}
		echo "<br/><a href='control.php'>Powrót do menu</a>";
		echo "</body>";	
	}
	
	function loadClients(){
		$handle = fopen("clients.csv", "r");
		$row=0;
		while (($data = fgetcsv($handle, 1000, ";")) == TRUE) 
		{
			$this->clients[$row]=array('imie'=>$data[0],'nazwisko'=>$data[1]);
			$row++;
		}
		fclose($handle);
	} // end function displayData()
	
	public function czyIstniejeKlient($imie, $nazwisko){
		for($i=0;$i<count($this->clients);$i++){
			if($this->clients[$i]['imie'] == $imie and $this->clients[$i]['nazwisko'] == $nazwisko){
				return true;
			}
		}
		return false;
	}
	
}
?>
