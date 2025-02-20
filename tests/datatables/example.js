var dataSet =	[
	['Product 1', [[10, 20]]],
	['Product 2', [[10, 20], [30, 40], [50, 60]]],
	['Product 3', [[100, 200]]],
	['Product 4', [[10, 20], [30, 40], [300, 400]]],
	['Product 5', [[2000, 2500], [3000, 3500]]],
	['Product 6', [[1000, 1200], [2000, 2200]]],
	['Product 7', [[10, 20], [100, 200]]],
	['Product 8', [[10, 20], [30, 40], [100, 200]]],
	['Product 9', [[10, 90], [300, 400], [1000, 1200], [2000, 2200]]],
	['Product 10', [[110, 120], [130, 140], [150, 160]]],
	['Product 11', [[10, 40], [90, 110]]],
	['Product 12', [[100, 200], [300, 400], [500, 600]]],
	['Product 13', [[1000, 1200]]],
	['Product 14', [[100, 200], [500, 600]]],
	['Product 15', [[300, 400]]],
	['Product 16', [[100, 200], [300, 400]]],
	['Product 17', [[10, 60]]],
	['Product 18', [[1000, 1200], [2000, 2200], [3000, 3200]]],
	['Product 19', [[200, 300], [530, 540]]],
	['Product 20', [[100, 500]]]
];


let table = new DataTable('#example', {
    columns: [
        { title: 'Name' },
        { title: 'Range' }
    ],
    data: dataSet
});

function SearchRanges(string, row, rowindex)
{
	let value = myInput.value

	if (value == '')
		return true;

	value = Number(value)

	if (Number.isNaN(value))
		return true;

	for (let range of row[1])
	{
		if (value >= range[0] && value <= range[1])
			return true;
	}

	return false;
}

$('#myInput').on('keyup', function () {
	table.search(SearchRanges).draw();
});
