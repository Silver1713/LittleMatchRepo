const fs = require('fs');
const path = require('path');


function replaceAllPaths(filePath) {

    let content = fs.readFileSync(filePath, 'utf8');


    const projectDir = path.dirname(filePath);


    const regex = /([a-zA-Z]:\\[^;"'<>\|\n\r]+)/g; // Match Window path only (e.g. C:\path\to\file)


    content = content.replace(regex, (match) => {
        const relativePath = path.relative(projectDir, match); // Get the relative path
        return relativePath.replace(/\\/g, '/'); // Normalize to forward slashes
    });

    // Write the modified content back to the file stream
    fs.writeFileSync(filePath, content, 'utf8');
    console.log('All absolute paths have been replaced with relative paths.');
}


const buildDir = 'build';
const files = fs.readdirSync(buildDir);
const vcxprojOrSlnFiles = files.filter(file => file.endsWith('.vcxproj') || file.endsWith('.sln'));


vcxprojOrSlnFiles.forEach(file => {
    replaceAllPaths(path.join(buildDir, file));
});


