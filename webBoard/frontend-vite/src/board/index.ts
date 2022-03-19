type Cell = {
    active: boolean;
}

type CellsRow = Cell[];

type Game = {
    field: CellsRow[];
}

const createCell = () : Cell => {
    return {
        active: false
    };
}

const createCellsRows = (width: number) : CellsRow => {
    const row : CellsRow = [];
    for (let i = 0; i < width; i++) {
        row.push(createCell());
    }
    return row;
}

const createField = (width: number, height: number) : CellsRow[] => {
    const rows : CellsRow[] = [];
    for (let i = 0; i < height; i++) {
        rows.push(createCellsRows(width));
    }
    return rows;
}

function createBoard(fieldWidth: number, fieldHeight: number) : Game {
    return {
        field: createField(fieldWidth, fieldHeight)
    };
}

export {
    createBoard
}