
class Range
{
  constructor(min, max)
  {
    this.min = min;
    this.max = max;
  }

  toString()
  {
    return `${this.min}-${this.max}`;
  }
}

class Ranges extends Array
{
  constructor(...entries)
  {
  	super();

	  for (let i = 0; i < entries.length; i += 2)
		{
			this.push(new Range(entries[i], entries[i + 1]))
		}
  }

  toString()
  {
    return this.join('<br>');
  }
}

function r(...entries)
{
	return new Ranges(...entries)
}

var dataSet =	[
	['Product 01', r(10.5, 20.5)],
	['Product 02', r(10, 20, 30, 40, 50, 60)],
	['Product 03', r(100.1, 200.9)],
	['Product 04', r(10, 20, 30, 40, 300, 400)],
	['Product 05', r(2000, 2500, 3000, 3500)],
	['Product 06', r(1000, 1200, 2000, 2200)],
	['Product 07', r(10, 20, 100, 200)],
	['Product 08', r(10, 20, 30, 40, 100, 200)],
	['Product 09', r(10, 90, 300, 400, 1000, 1200, 2000, 2200)],
	['Product 10', r(110, 120, 130, 140, 150, 160)],
	['Product 11', r(10, 40, 90, 110)],
	['Product 12', r(100, 200, 300, 400, 500, 600)],
	['Product 13', r(1000, 1200)],
	['Product 14', r(100, 200, 500, 600)],
	['Product 15', r(300, 400)],
	['Product 16', r(100, 200, 300, 400)],
	['Product 17', r(10, 60)],
	['Product 18', r(1000, 1200, 2000, 2200, 3000, 3200)],
	['Product 19', r(200, 300, 530, 540)],
	['Product 20', r(100, 500)]
];

let table = new DataTable('#example',
{
  columns:
  [
    { title: 'Name' },
		{ title: 'Range' }
  ],
  data: dataSet,
  layout:
  {
      topStart: function ()
      {
        let toolbar = document.createElement('div');
        toolbar.innerHTML = 'Range Search: <input type="text" id="RangeSearchInput" />';
        return toolbar;
      },
      topEnd: 'search',
      bottomStart: ['info', 'pageLength'],
      bottomEnd: 'paging'
  }
});

let searchvalue = NaN

function SearchRanges(string, row, rowindex)
{
	if (Number.isNaN(searchvalue))
		return true;

	for (let range of row[1])
	{
		if (searchvalue >= range.min && searchvalue <= range.max)
			return true;
	}

	return false;
}

$('#RangeSearchInput').on('keyup', function()
{
	let value = RangeSearchInput.value;
	searchvalue = value == '' ? NaN : Number(value);

	table.search(SearchRanges).draw();
});
