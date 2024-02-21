<?php
    // sets $page and $link
    require_once("header.php");

    if ($page === "login") {
        require_once("form.php"); // login form

        if(isset($_POST['username']) && isset($_POST['password'])) {
            // We use prepared statements to prevent SQL injections!
            $stmt = $link->prepare("SELECT mail, password FROM utenti WHERE username = ? AND password = ?");
            $stmt->bind_param("ss", $_POST['username'], $_POST['password']);
            if (!$stmt->execute()) {
                die('mysql error: '. mysqli_error($stmt->error()));
            }
            $result = $stmt->get_result();
            $stmt->close();

            if ( $result->fetch_array() ) {
                // query is successful we let the user in!
                $_SESSION['username']=$_POST['username'];
                header("Location: index.php?page=user");
            } else {
                // wrong credentials!
                echo '<div class="alert alert-danger" role="alert">Login failed!</div>';
            }
        }
    }
    if ($page === "user") {
        require_once("greetings.php");

        // shows user's data:
        if (isset($_GET['show_data'])) {
            // We retrieve data using the registered username taken
            // from the current session $_SESSION['username']
            // NOTE: this is NOT user input, is stored in the server!
            // no SQL injection is possible here ...
            echo "<p>Personal data:</p>";
            $query = "SELECT * FROM utenti WHERE username = '" . $_SESSION['username'] . "'";
            $result = $link->query($query);
            if (!$result) {
                var_dump($query); // Showing the query is instructive!
                die('mysql error: '. mysqli_error($link));
            } else {
                $data = $result->fetch_array(MYSQLI_ASSOC);
                if (count((array) $data) > 0) {
                    echo '<table >';
                    echo '<tr><td>Username: </td><td>', $data['username'],' </td></tr>';
                    echo '<tr><td>Name:     </td><td>', $data['name'],' </td></tr>';
                    echo '<tr><td>Lastname: </td><td>', $data['lastname'],' </td></tr>';
                    echo '<tr><td>email:    </td><td>', $data['mail'],' </td></tr>';
                    echo '<tr><td>url:      </td><td>', $data['url'],' </td></tr>';
                    echo '<tr><td>Password: </td><td> (hidden) </td></tr>';
                    echo '</table>';
                    echo '<p><a href="index.php?page=user">Hide</a></p>';
                }
            }
        }
    }
    if ($page === "registration") {
        require_once("formReg.php"); // registration form

        if(isset($_POST['username'])){
            if (!$_POST['username'] || !$_POST['password']) {
                echo '<p>ERROR: please set at least username and password</p>';
            } else {
                // We use prepared statements to prevent SQL injections!

                // Let's first check that username is not taken
                $stmt = $link->prepare("SELECT 1 FROM utenti WHERE username = ?");
                $stmt->bind_param("s", $_POST['username']);
                if (!$stmt->execute()) {
                    die('mysql error: '. mysqli_error($stmt->error()));
                }
                $result = $stmt->get_result();
                $stmt->close();

                if ( $result->fetch_array() ) {
                    echo '<p>ERROR: username ' . $_POST['username'] . ' already taken, sorry!</p>';
                } else {
                    // username is available!
                    // We use prepared statements to prevent SQL injections!
                    $stmt = $link->prepare("INSERT INTO utenti (username, password, name,lastname, mail, url) VALUES (?,?,?,?,?,?)");
                    $stmt->bind_param("ssssss", $_POST['username'],$_POST['password'],$_POST['name'],$_POST['lastname'],$_POST['mail'],$_POST['url']);

                    if (!$stmt->execute()) {
                        die('mysql error: '. mysqli_error($stmt->error()));
                    }
                    echo '<p> User ' . $_POST['username'] . ' succesfully added!</p>';
                    echo '<p> Go to the <a href="index.php?page=login">log in page</a></p>';
                }
            }
        }
    }
    if ($page === "logout") {
        unset($_SESSION['username']);
        header("Location: index.php?page=login");
    }

    require_once('footer.php');
?>


