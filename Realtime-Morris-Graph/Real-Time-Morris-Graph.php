/*
    Live updating morris-js graph without refreshing the page
    
    generate_grap.php is a script which generates an array of data by querying the Database.
    display_graph makes an http request to generate_graph.php and updates the graph object.

    Database :

    +--------------+   +--------------+
    | Patients     |   |     Data     |
    +--------------+   +--------------+
    | id (primary) |   | id (primary) |
    |              | ↘ | id_patient   |
    |              |   | timestamp    |
    |              |   | temperature  |
    |              |   | pulse_rate   |
    +--------------+   +--------------+
*/


/*
    display_graph.php
*/

<?php
    require_once('Database.php')
    require_once('Patients.php');

    $database = connectToDatabase(); // return a PDO object

    $patientsManager = new PatientsManager();
    $patient = $patientsManager->getPatient($database, $_GET['id']); // SELECT * FROM Patients WHERE id = $_GET['id']
?>

<html>
    <head>
            <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.css">
            <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
            <script src="//cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js"></script>
            <script src="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.min.js"></script>
    </head>
    <body>
        <div id="morris_graph" style="height: 250px;"></div>
    </body>
</html>


<script>
    $(document).ready(function() {
        draw_graph();
        setInterval(function() {
            $("#morris_graph").empty();
            draw_graph();
        }, 5000)
    });

    function draw_graph() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", '<?php echo "generate_graph.php?id=" . $patient['id '];?>', false);
        xhr.send(null);
        eval(xhr.responseText);
    }
</script>

/*
    generate_graph.php
*/

<?php
require_once ('Data.php');
require_once ('Patients.php');
require_once ('Database.php');

$database = connectToDatabase();

$patientsManager = new PatientsManager();
$patient = $patientsManager->getPatient($database, $_GET['id']); // SELECT * FROM Patients WHERE id = $_GET['id']

$dataManager = new DataManager();
$dataArray = $dataManager->getData($database, $_GET['id']); // SELECT * FROM Data WHERE id_patient = $_GET['id']


echo 'new Morris.Line({';
echo 'element: \'morris_graph\',';
echo 'data: [';
foreach ($dataArray as &$data) {
    echo '{';
    echo 'm: \'' . date('Y-m-d h:i:s', strtotime($data['hour'])) . '\',';
    echo 'a: ' . intval($data['temperature']) . ',';
    echo 'b: ' . intval($data['pulse_rate']);
    echo '},';
}
echo '],';
echo 'xkey: \'m\',';
echo 'ykeys: [\'a\', \'b\'],';
echo 'labels: [\'Temperature\', \'Pulse Rate\']';
echo '});';
?>
